#include <cstring>
#include <cstdint>

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/var_array_buffer.h"
#include "ppapi/cpp/var_dictionary.h"

const char *kEcho = "Echo from NaCl: ";

/**
 * This is a base of your NaCl application. There is one instance of
 * <code>pp::Instance</code> class object per <embed> element on a web page.
 */
class NaClInstance : public pp::Instance {
 public:
  explicit NaClInstance(PP_Instance instance) : pp::Instance(instance) {}

  /**
   * Retrieves buffer with binary data from the dictionary for the given key.
   * @param error Output parameter: 0 means success, other value - error.
   * @param len The length of the returned buffer.
   * @return The newly allocated buffer - must be freed by the caller via the
   * free() call.
   */
  static unsigned char *getArrayBufferFromDictionary(
      pp::VarDictionary &dictionary, const char *key, int *error,
      uint32_t *len) {
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

    const unsigned char *buffer = (unsigned char *)value_var.Map();
    if (buffer) {
      unsigned char *retval =
          static_cast<unsigned char *>(calloc(*len, sizeof(unsigned char)));
      memcpy(retval, buffer, *len);
      value_var.Unmap();
      *error = 0;
      return retval;
    }
    *error = 1;
    return 0;
  }

  /**
   * Performs basic validation of the message.
   *
   * @param message_data The message data
   * @return true if the message is a dictionary.
   */
  static bool validateMessage(const pp::Var &message_data) {
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
  static int getMessageId(const pp::Var &message) {
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
   * Handles messages from JS sent by <code>nacl_module.postMessage(...)</code>.
   * @see <code>HandleMessage</code> in <toolchain>/ppapi/cpp/instance.h file
   * for more details.
   */
  virtual void HandleMessage(const pp::Var &message) {
    // TODO: Add your communication NaCl<->JavaScript here:
    // PostMessage("Message");
    // You can also use Message Template Generator to generate functions
    // automatically
    //
    if (message.is_string()) {
      PostMessage(kEcho + message.AsString() + "\n");
      return;
    }

    const int msgIdNumber = getMessageId(message);
    if (msgIdNumber < 0) {
      return;
    }
    // Passes the message to a proper handler function.
    switch (msgIdNumber) {
      case 0: {
        pp::VarDictionary dict(message);
        break;
      }
      case 1: {
        pp::VarDictionary dict(message);
        break;
      }
      case 2: {
        pp::VarDictionary dict(message);
        break;
      }
      case 3: {
        pp::VarDictionary dict(message);
        break;
      }
      case 4: {
        pp::VarDictionary dict(message);
        break;
      }
      case 5: {
        pp::VarDictionary dict(message);
        {
          int error = 0;
          uint32_t len = 0;
          getArrayBufferFromDictionary(dict, "buffer", &error, &len);
        }
        break;
      }
      case 6: {
        pp::VarDictionary dict(message);
        break;
      }
      case 7: {
        break;
      }
      case 8: {
        break;
      }
      case 9: {
        pp::VarDictionary dict(message);
        break;
      }
      default:
        break;
    }
  }

  /**
   * Initializes this instance with provided arguments listed in the <embed>
   * tag.
   * @see <code>Init()</code> in <toolchain>/ppapi/cpp/instance.h file for more
   * details.
   */
  virtual bool Init(uint32_t argc, const char *argn[], const char *argv[]) {
    return true;
  }
};

/**
 * A NaCl app must have one class that implements <code>pp::Module</code>.
 */
class NaClModule : public pp::Module {
 public:
  /**
   * This method is called every time a browser encounters an <embed> element
   * on a web page.
   */
  virtual pp::Instance *CreateInstance(PP_Instance instance) {
    return new NaClInstance(instance);
  }
};

namespace pp {

/**
 * This function is an entry point to a NaCl application.
 */
Module *CreateModule() { return new NaClModule(); }

}  // namespace pp
