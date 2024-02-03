/**
 * @file communication.js
 * @brief NaCl application communication handler.
 * All NaCl <-> JS communication should be implemented in this file.
 */

/**
 * This function is called when a message from NaCl arrives.
 */
function handleNaclMessage(message_event) {
   var message = message_event.data;

   if (typeof message['messageID'] !== 'undefined') {
      switch (message['messageID']) {
         case 1:
            break;
         case 2:
            break;
         case 3:
            break;
         case 4:
            break;
         case 5:
            break;
         case 6:
            break;
         case 7:
            break;
         case 8:
            break;
         case 9:
            break;
         default:
            // Unknown message
            break;
      }
   }
   if (printIfLog(message)) {  // function defined in common.js
      return;   // this was a log or error message, so we can finish this handling
   }
}

function calledOnLoad() {
   nacl_module.postMessage("Hello from Js");
  /* Fill this function with your code (if needed). */
}


/*
 * WARNING: Handling of dictionaries used by NaCl communication can cause problems if
 * Object.prototype in JS is modified, which results in not receiving messages in NaCl plugin.
 * Do not change Object.prototype if you are using complex types (dictionary, table) or
 * generator to generate JS->NaCl communication. If you need to modify Object.prototype, you
 * need to write your own send* functions using only simple types as message.
 */