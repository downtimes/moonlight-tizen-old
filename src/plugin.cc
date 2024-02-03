#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/var_array_buffer.h"
#include <cstring>
#include "ppapi/cpp/var_dictionary.h"

/**
 * This is a base of your NaCl application. There is one instance of
 * <code>pp::Instance</code> class object per <embed> element on a web page.
 */
class NaClInstance : public pp::Instance {
 public:

/**
 * Struct holding data for the 'tcpSocketSetOptionResponse' message.
 */
struct tcpSocketSetOptionResponse_Data {
  int code; // Zero if succeed, otherwise an error code from pp_errors.h.
};


/**
 * Method for posting the 'tcpSocketSetOptionResponse' message.
 *
 * @param data The message's data
 * @see tcpSocketSetOptionResponse_Data
 */
void PostMessage_tcpSocketSetOptionResponse(const tcpSocketSetOptionResponse_Data& data) {
  pp::VarDictionary dict;
  dict.Set(pp::Var("messageID"), pp::Var(9));
  dict.Set(pp::Var("code"), pp::Var(data.code));
  PostMessage(dict);
}


/**
 * Struct holding data for the 'tcpSocketSetOption' message.
 */
struct tcpSocketSetOption_Data {
  int option; // The option to set. Please see the PP_TCPSocket_Option description for option names, value types and allowed values.
  std::string value; // The option value to set.
};


/**
 * Handler for the 'tcpSocketSetOption' message.
 *
 * @param data The message's data
 * @see tcpSocketSetOption_Data
 */
void HandleMessage_tcpSocketSetOption(const tcpSocketSetOption_Data& data) {
  // TODO: Add your message handling code here
}

/**
 * Handler for the 'tcpSocketClose' message.
 */
void HandleMessage_tcpSocketClose() {
  // TODO: Add your message handling code here
}


/**
 * Struct holding data for the 'tcpSocketAcceptResponse' message.
 */
struct tcpSocketAcceptResponse_Data {
  std::string address; // An address of accepted connection as host:port.
  int code; // Zero if succeed, otherwise an error code from pp_errors.h.
};


/**
 * Method for posting the 'tcpSocketAcceptResponse' message.
 *
 * @param data The message's data
 * @see tcpSocketAcceptResponse_Data
 */
void PostMessage_tcpSocketAcceptResponse(const tcpSocketAcceptResponse_Data& data) {
  pp::VarDictionary dict;
  dict.Set(pp::Var("messageID"), pp::Var(8));
  dict.Set(pp::Var("address"), pp::Var(data.address));
  dict.Set(pp::Var("code"), pp::Var(data.code));
  PostMessage(dict);
}

/**
 * Handler for the 'tcpSocketAccept' message.
 */
void HandleMessage_tcpSocketAccept() {
  // TODO: Add your message handling code here
}


/**
 * Struct holding data for the 'tcpSocketListenResponse' message.
 */
struct tcpSocketListenResponse_Data {
  int code; // Zero if succeed, otherwise an error code from pp_errors.h.
};


/**
 * Method for posting the 'tcpSocketListenResponse' message.
 *
 * @param data The message's data
 * @see tcpSocketListenResponse_Data
 */
void PostMessage_tcpSocketListenResponse(const tcpSocketListenResponse_Data& data) {
  pp::VarDictionary dict;
  dict.Set(pp::Var("messageID"), pp::Var(7));
  dict.Set(pp::Var("code"), pp::Var(data.code));
  PostMessage(dict);
}


/**
 * Struct holding data for the 'tcpSocketListen' message.
 */
struct tcpSocketListen_Data {
  int backlog; // A hint to determine the maximum length to which the queue of pending connections may grow.
};


/**
 * Handler for the 'tcpSocketListen' message.
 *
 * @param data The message's data
 * @see tcpSocketListen_Data
 */
void HandleMessage_tcpSocketListen(const tcpSocketListen_Data& data) {
  // TODO: Add your message handling code here
}


/**
 * Struct holding data for the 'tcpSocketWriteResponse' message.
 */
struct tcpSocketWriteResponse_Data {
  int code; // A non-negative number on success to indicate how many bytes have been written; otherwise, an error code from pp_errors.h.
};


/**
 * Method for posting the 'tcpSocketWriteResponse' message.
 *
 * @param data The message's data
 * @see tcpSocketWriteResponse_Data
 */
void PostMessage_tcpSocketWriteResponse(const tcpSocketWriteResponse_Data& data) {
  pp::VarDictionary dict;
  dict.Set(pp::Var("messageID"), pp::Var(6));
  dict.Set(pp::Var("code"), pp::Var(data.code));
  PostMessage(dict);
}
/**
 * Retrieves buffer with binary data from the dictionary for the given key.
 * @param error Output parameter: 0 means success, other value - error.
 * @param len The length of the returned buffer.
 * @return The newly allocated buffer - must be freed by the caller via the free() call.
 */
static unsigned char* getArrayBufferFromDictionary(pp::VarDictionary& dictionary, const char* key, int* error, uint32_t* len) {
  pp::VarArrayBuffer value_var(dictionary.Get(pp::Var(key)));
  if (!value_var.is_array_buffer()) {
    *error = 1;
    return 0;
  }

  *len = value_var.ByteLength();
  if (*len < 1) {
    *error = 1;
    return 0;
  }

  const unsigned char* buffer = (unsigned char*) value_var.Map();
  if (buffer) {
    unsigned char* retval = static_cast<unsigned char*>(calloc(*len, sizeof(unsigned char)));
    memcpy(retval, buffer, *len);
    value_var.Unmap();
    *error = 0;
    return retval;
  }
  *error = 1;
  return 0;
}


/**
 * Struct holding data for the 'tcpSocketWrite' message.
 */
struct tcpSocketWrite_Data {
  struct {
    unsigned char* buffer;
    uint32_t length;
  } buffer; // Buffer with data to send.
  int bytesToSend; // Number of bytes to send.
};


/**
 * Handler for the 'tcpSocketWrite' message.
 *
 * @param data The message's data
 * @see tcpSocketWrite_Data
 */
void HandleMessage_tcpSocketWrite(const tcpSocketWrite_Data& data) {
  // TODO: Add your message handling code here
}


/**
 * Struct holding data for the 'tcpSocketReadResponse' message.
 */
struct tcpSocketReadResponse_Data {
  struct {
    unsigned char* buffer;
    uint32_t length;
  } buffer; // Buffer with read data.
  int bytesRead; // The number of bytes to read.
  int code; // A non-negative number on success to indicate how many bytes have been read, 0 means that end-of-file was reached; otherwise, an error code from pp_errors.h
};


/**
 * Method for posting the 'tcpSocketReadResponse' message.
 *
 * @param data The message's data
 * @see tcpSocketReadResponse_Data
 */
void PostMessage_tcpSocketReadResponse(const tcpSocketReadResponse_Data& data) {
  pp::VarDictionary dict;
  dict.Set(pp::Var("messageID"), pp::Var(5));
  {
    pp::VarArrayBuffer varbuffer(data.buffer.length);
    unsigned char* bufbuffer = static_cast<unsigned char*>(varbuffer.Map());
    memcpy(bufbuffer, data.buffer.buffer, data.buffer.length);
    varbuffer.Unmap();
    dict.Set(pp::Var("buffer"), varbuffer);
  }
  dict.Set(pp::Var("bytesRead"), pp::Var(data.bytesRead));
  dict.Set(pp::Var("code"), pp::Var(data.code));
  PostMessage(dict);
}


/**
 * Struct holding data for the 'tcpSocketRead' message.
 */
struct tcpSocketRead_Data {
  int bytesToRead; // Number of bytes to read.
};


/**
 * Handler for the 'tcpSocketRead' message.
 *
 * @param data The message's data
 * @see tcpSocketRead_Data
 */
void HandleMessage_tcpSocketRead(const tcpSocketRead_Data& data) {
  // TODO: Add your message handling code here
}


/**
 * Struct holding data for the 'tcpSocketConnectResponse' message.
 */
struct tcpSocketConnectResponse_Data {
  int code; // Zero if succeed, otherwise an error code from pp_errors.h.
};


/**
 * Method for posting the 'tcpSocketConnectResponse' message.
 *
 * @param data The message's data
 * @see tcpSocketConnectResponse_Data
 */
void PostMessage_tcpSocketConnectResponse(const tcpSocketConnectResponse_Data& data) {
  pp::VarDictionary dict;
  dict.Set(pp::Var("messageID"), pp::Var(4));
  dict.Set(pp::Var("code"), pp::Var(data.code));
  PostMessage(dict);
}


/**
 * Struct holding data for the 'tcpSocketConnect' message.
 */
struct tcpSocketConnect_Data {
  std::string host; // Host name or IP address
  int port; // Port number from 0 to 65535.
};


/**
 * Handler for the 'tcpSocketConnect' message.
 *
 * @param data The message's data
 * @see tcpSocketConnect_Data
 */
void HandleMessage_tcpSocketConnect(const tcpSocketConnect_Data& data) {
  // TODO: Add your message handling code here
}


/**
 * Struct holding data for the 'tcpSocketBindResponse' message.
 */
struct tcpSocketBindResponse_Data {
  int code; // Zero if succeed, otherwise an error code from pp_errors.h.
};


/**
 * Method for posting the 'tcpSocketBindResponse' message.
 *
 * @param data The message's data
 * @see tcpSocketBindResponse_Data
 */
void PostMessage_tcpSocketBindResponse(const tcpSocketBindResponse_Data& data) {
  pp::VarDictionary dict;
  dict.Set(pp::Var("messageID"), pp::Var(3));
  dict.Set(pp::Var("code"), pp::Var(data.code));
  PostMessage(dict);
}


/**
 * Struct holding data for the 'tcpSocketBind' message.
 */
struct tcpSocketBind_Data {
  std::string host; // Host name or IP address
  int port; // Port number from 0 to 65535.
};


/**
 * Handler for the 'tcpSocketBind' message.
 *
 * @param data The message's data
 * @see tcpSocketBind_Data
 */
void HandleMessage_tcpSocketBind(const tcpSocketBind_Data& data) {
  // TODO: Add your message handling code here
}


/**
 * Struct holding data for the 'tcpSocketGetRemoteAddressResponse' message.
 */
struct tcpSocketGetRemoteAddressResponse_Data {
  std::string address; // Network address with optional port number as host[:port_num]
};


/**
 * Method for posting the 'tcpSocketGetRemoteAddressResponse' message.
 *
 * @param data The message's data
 * @see tcpSocketGetRemoteAddressResponse_Data
 */
void PostMessage_tcpSocketGetRemoteAddressResponse(const tcpSocketGetRemoteAddressResponse_Data& data) {
  pp::VarDictionary dict;
  dict.Set(pp::Var("messageID"), pp::Var(2));
  dict.Set(pp::Var("address"), pp::Var(data.address));
  PostMessage(dict);
}


/**
 * Struct holding data for the 'tcpSocketGetRemoteAddress' message.
 */
struct tcpSocketGetRemoteAddress_Data {
  bool asIPv6; // Set true if should get IPv6 address, otherwise will return IPv4.
  bool withPort; // Set true if address should contain port as :<port_num>
};


/**
 * Handler for the 'tcpSocketGetRemoteAddress' message.
 *
 * @param data The message's data
 * @see tcpSocketGetRemoteAddress_Data
 */
void HandleMessage_tcpSocketGetRemoteAddress(const tcpSocketGetRemoteAddress_Data& data) {
  // TODO: Add your message handling code here
}


/**
 * Struct holding data for the 'tcpSocketGetLocalAddressResponse' message.
 */
struct tcpSocketGetLocalAddressResponse_Data {
  std::string address; // Network address with optional port number as host[:port_num]
};


/**
 * Method for posting the 'tcpSocketGetLocalAddressResponse' message.
 *
 * @param data The message's data
 * @see tcpSocketGetLocalAddressResponse_Data
 */
void PostMessage_tcpSocketGetLocalAddressResponse(const tcpSocketGetLocalAddressResponse_Data& data) {
  pp::VarDictionary dict;
  dict.Set(pp::Var("messageID"), pp::Var(1));
  dict.Set(pp::Var("address"), pp::Var(data.address));
  PostMessage(dict);
}

  /**
   * Performs basic validation of the message.
   *
   * @param message_data The message data
   * @return true if the message is a dictionary.
   */
  static bool validateMessage(const pp::Var& message_data) {
    if (!message_data.is_dictionary()) {
      return false;
    }
    return true;
  }

/**
 * Retrieves the message id from the message.
 * @param message The message.
 * @return The message id in case of success.
 * -1 in case the message is not a dictionary instance.
 * -2 in case the message does not contain proper
 *    'messageID' key with an integer value.
 */
static int getMessageId(const pp::Var& message) {
  if (!validateMessage(message)) {
    return -1;
  }
  pp::VarDictionary dict(message);
  // Extracting the message's Id.
  pp::Var msgId = dict.Get(pp::Var("messageID"));
  if (!msgId.is_int()) {
    return -2;
  }
  return msgId.AsInt();
}


/**
 * Struct holding data for the 'tcpSocketGetLocalAddress' message.
 */
struct tcpSocketGetLocalAddress_Data {
  bool asIPv6; // Set true if should get IPv6 address, otherwise will return IPv4.
  bool withPort; // Set true if address should contain port as [:port_num]
};


/**
 * Handler for the 'tcpSocketGetLocalAddress' message.
 *
 * @param data The message's data
 * @see tcpSocketGetLocalAddress_Data
 */
void HandleMessage_tcpSocketGetLocalAddress(const tcpSocketGetLocalAddress_Data& data) {
  // TODO: Add your message handling code here
}


  explicit NaClInstance(PP_Instance instance)
      : pp::Instance(instance) {
  }

  virtual ~NaClInstance() {
  }

  /**
   * Handles messages from JS sent by <code>nacl_module.postMessage(...)</code>.
   * @see <code>HandleMessage</code> in <toolchain>/ppapi/cpp/instance.h file for more details.
   */
  virtual void HandleMessage(const pp::Var& message) {
    // TODO: Add your communication NaCl<->JavaScript here:
    // PostMessage("Message");
    // You can also use Message Template Generator to generate functions automatically
    
  
  const int msgIdNumber = getMessageId(message);
  if (msgIdNumber < 0) {
    return;
  }
  // Passes the message to a proper handler function.
  switch (msgIdNumber) {
      case 0: {
        pp::VarDictionary dict(message);
        tcpSocketGetLocalAddress_Data data;
        data.asIPv6 = dict.Get(pp::Var("asIPv6")).AsBool();
        data.withPort = dict.Get(pp::Var("withPort")).AsBool();
        HandleMessage_tcpSocketGetLocalAddress(data);
        break;
      }
      case 1: {
      pp::VarDictionary dict(message);
      tcpSocketGetRemoteAddress_Data data;
      data.asIPv6 = dict.Get(pp::Var("asIPv6")).AsBool();
      data.withPort = dict.Get(pp::Var("withPort")).AsBool();
      HandleMessage_tcpSocketGetRemoteAddress(data);
      break;
    }
    case 2: {
      pp::VarDictionary dict(message);
      tcpSocketBind_Data data;
      data.host = dict.Get(pp::Var("host")).AsString();
      data.port = dict.Get(pp::Var("port")).AsInt();
      HandleMessage_tcpSocketBind(data);
      break;
    }
    case 3: {
      pp::VarDictionary dict(message);
      tcpSocketConnect_Data data;
      data.host = dict.Get(pp::Var("host")).AsString();
      data.port = dict.Get(pp::Var("port")).AsInt();
      HandleMessage_tcpSocketConnect(data);
      break;
    }
    case 4: {
      pp::VarDictionary dict(message);
      tcpSocketRead_Data data;
      data.bytesToRead = dict.Get(pp::Var("bytesToRead")).AsInt();
      HandleMessage_tcpSocketRead(data);
      break;
    }
    case 5: {
      pp::VarDictionary dict(message);
      tcpSocketWrite_Data data;
      {
        int error = 0;
        data.buffer.buffer = getArrayBufferFromDictionary(dict, "buffer", &error, &data.buffer.length);
      }
      data.bytesToSend = dict.Get(pp::Var("bytesToSend")).AsInt();
      HandleMessage_tcpSocketWrite(data);
      break;
    }
    case 6: {
      pp::VarDictionary dict(message);
      tcpSocketListen_Data data;
      data.backlog = dict.Get(pp::Var("backlog")).AsInt();
      HandleMessage_tcpSocketListen(data);
      break;
    }
    case 7: {
      HandleMessage_tcpSocketAccept();
      break;
    }
    case 8: {
      HandleMessage_tcpSocketClose();
      break;
    }
    case 9: {
      pp::VarDictionary dict(message);
      tcpSocketSetOption_Data data;
      data.option = dict.Get(pp::Var("option")).AsInt();
      data.value = dict.Get(pp::Var("value")).AsString();
      HandleMessage_tcpSocketSetOption(data);
      break;
    }
  default: {

    }
  }
}

  /**
   * Initializes this instance with provided arguments listed in the <embed>
   * tag.
   * @see <code>Init()</code> in <toolchain>/ppapi/cpp/instance.h file for more details.
   */
  virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]) {
    return true;
  }
};

/**
 * A NaCl app must have one class that implements <code>pp::Module</code>.
 */
class NaClModule : public pp::Module {
 public:
  NaClModule()
      : pp::Module() {
  }

  virtual ~NaClModule() {
  }

  /**
   * This method is called every time a browser encounters an <embed> element
   * on a web page.
   */
  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new NaClInstance(instance);
  }
};

namespace pp {

/**
 * This function is an entry point to a NaCl application.
 */
Module* CreateModule() {
  return new NaClModule();
}

}  // namespace pp
