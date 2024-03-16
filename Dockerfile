FROM ubuntu:22.04 as build

ARG DEBIAN_FRONTEND=noninteractive

# Needed so that expect doesn't ask for a timezone during installation
ENV TZ=Etc/UTC
RUN apt-get update && apt-get install -y unzip wget make python2 expect && rm -rf /var/lib/apt/lists/*

# The build toolchain expects python2 to be available as python in path
# but Ubuntu only provides /usr/bin/python2.
RUN ln -sf /usr/bin/python2 /usr/bin/python

# Use a non-root user from here on
RUN useradd -m -s /bin/bash moonlight
USER moonlight
WORKDIR /home/moonlight

# Install Tizen Studio
# get file: web-cli_Tizen_Studio_5.0_ubuntu-64.bin
RUN wget -nv -O web-cli_Tizen_Studio_5.0_ubuntu-64.bin 'https://download.tizen.org/sdk/Installer/tizen-studio_5.0/web-cli_Tizen_Studio_5.0_ubuntu-64.bin'
RUN chmod a+x web-cli_Tizen_Studio_5.0_ubuntu-64.bin
RUN ./web-cli_Tizen_Studio_5.0_ubuntu-64.bin --accept-license /home/moonlight/tizen-studio
ENV PATH=/home/moonlight/tizen-studio/tools/ide/bin:/home/moonlight/tizen-studio/tools:${PATH}

# Prepare Tizen signing cerficates
RUN tizen certificate \
	-a Moonlight \
	-f Moonlight \
	-p 1234
RUN tizen security-profiles add \
	-n Moonlight \
	-a /home/moonlight/tizen-studio-data/keystore/author/Moonlight.p12 \
	-p 1234

# Workaround to package applications without gnome-keyring
# These steps must be repeated each time prior to packaging an application. 
# See <https://developer.tizen.org/forums/sdk-ide/pwd-fle-format-profile.xml-certificates>
RUN sed -i 's|/home/moonlight/tizen-studio-data/keystore/author/Moonlight.pwd||' /home/moonlight/tizen-studio-data/profile/profiles.xml
RUN sed -i 's|/home/moonlight/tizen-studio-data/tools/certificate-generator/certificates/distributor/tizen-distributor-signer.pwd|tizenpkcs12passfordsigner|' /home/moonlight/tizen-studio-data/profile/profiles.xml

RUN wget -nv -O pepper_v63.zip https://developer.samsung.com/smarttv/file/55e181c4-fb5e-4d25-82df-f85b3b864dab
RUN unzip pepper_v63.zip

# Copy all files into the container
COPY --chown=moonlight . ./moonlight-tizen-old
WORKDIR moonlight-tizen-old

RUN NACL_SDK_ROOT=/home/moonlight/pepper_63 make -j$(nproc)
RUN NACL_SDK_ROOT=/home/moonlight/pepper_63 make package

# Package and sign application 
# Effectively runs `tizen package -t wgt -- build/widget`,
# but uses an expect cmdfile to automate the password prompt.
RUN echo \
	'set timeout -1\n' \
	'spawn tizen package -t wgt -- build\n' \
	'expect "Author password:"\n' \
	'send -- "1234\\r"\n' \
	'expect "Yes: (Y), No: (N) ?"\n' \
	'send -- "N\\r"\n' \
	'expect eof\n' \
| expect

WORKDIR ..
RUN mv moonlight-tizen-old/build/MoonlightTizenOld.wgt .

# remove unneed files
RUN rm -rf \
	moonlight-tizen-old \
	pepper_63 \
	pepper_v63.zip \
	tizen-package-expect.sh \
	web-cli_Tizen_Studio_5.0_ubuntu-64.bin \
	.package-manager \
	.wget-hsts

# Build the image with only the tizen toolchain and the generated .wgt to save space
FROM ubuntu:22.04

COPY --from=build / /

USER moonlight
WORKDIR /home/moonlight

# Add Tizen Studio to path
ENV PATH=/home/moonlight/tizen-studio/tools/ide/bin:/home/moonlight/tizen-studio/tools:${PATH}