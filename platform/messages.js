/* eslint-disable */

var callbacks = {}
var callbacks_ids = 1;

/**
 * var sendMessage - Sends a message with arguments to the NaCl module
 *
 * @param  {String} method A named method
 * @param  {(String|Array)} params An array of options or a signle string
 * @return {void}        The NaCl module calls back trought the handleMessage method
 */
var sendMessage = function (method, params) {
  return new Promise(function (resolve, reject) {
    var id = callbacks_ids++;
    callbacks[id] = {
      'resolve': resolve,
      'reject': reject
    };

    common.nacl_module.postMessage({
      'callbackId': id,
      'method': method,
      'params': params
    });
  });
}

/**
 * handleMessage - Handles messages from the NaCl module
 *
 * @param  {Object} msg An object given by the NaCl module
 * @return {void}
 */
function handleMessage(msg) {
  common.updateStatus("Handle message called: " + msg);
  if (msg.callbackId && callbacks[msg.callbackId]) { // if it's a callback, treat it as such
    common.updateStatus("callback called")
    callbacks[msg.callbackId][msg.ta.type](msg.ret);
    delete callbacks[msg.callbackId]
  } else { // else, it's just info, or an event
    console.log('%c[messages.js, handleMessage]', 'color:gray;', 'Message data: ', msg)
    if (msg.indexOf('streamTerminated: ') === 0) { // if it's a recognized event, notify the appropriate function
      // Release our keep awake request
      if (runningOnChrome()) {
        chrome.power.releaseKeepAwake();
      }

      // Show a termination snackbar message if the termination was unexpected
      var errorCode = parseInt(msg.replace('streamTerminated: ', ''));
      switch (errorCode) {
        case 0: // ML_ERROR_GRACEFUL_TERMINATION
          break;

        case -100: // ML_ERROR_NO_VIDEO_TRAFFIC
          snackbarLogLong("No video received from host. Check the host PC's firewall and port forwarding rules.");
          break;

        case -101: // ML_ERROR_NO_VIDEO_FRAME
          snackbarLogLong("Your network connection isn't performing well. Reduce your video bitrate setting or try a faster connection.");
          break;

        default:
          snackbarLogLong("Connection terminated");
          break;
      }

      api.refreshServerInfo().then(function (ret) {
        // Return to app list with new currentgame
        showApps(api);
      }, function () {
        // Return to app list anyway
        showApps(api);
      });
    } else if (msg === 'Connection Established') {
      $('#loadingSpinner').css('display', 'none');
      $('body').css('backgroundColor', 'black');
      $("#nacl_module").css("display", "");
      $("#nacl_module").focus();

      // Keep the display awake while streaming
      if (runningOnChrome()) {
        chrome.power.requestKeepAwake("display");
      }
    } else if (msg.indexOf('ProgressMsg: ') === 0) {
      $('#loadingMessage').text(msg.replace('ProgressMsg: ', ''));
    } else if (msg.indexOf('TransientMsg: ') === 0) {
      snackbarLog(msg.replace('TransientMsg: ', ''));
    } else if (msg.indexOf('DialogMsg: ') === 0) {
      // FIXME: Really use a dialog
      snackbarLogLong(msg.replace('DialogMsg: ', ''));
    } else if (msg === 'displayVideo') {
      // Show the video stream now
      $("#nacl_module")[0].style.opacity = 1.0;
      $("#listener").addClass("fullscreen");
    } 
//    TODO: Seems to have code that is not compatible with the javascript version in code.
//    else if (msg.indexOf('controllerRumble: ') === 0) {
//      const eventData = msg.data.split(' ')[1].split(',');
//      const gamepadIdx = parseInt(eventData[0]);
//      const weakMagnitude = parseFloat(eventData[1]);
//      const strongMagnitude = parseFloat(eventData[2]);
//      console.log("Playing rumble on gamepad " + gamepadIdx + " with weakMagnitude " + weakMagnitude + " and strongMagnitude " + strongMagnitude);
//
//      // We may not actually have a gamepad at this index.
//      // Even if we do have a gamepad, it may not have a vibrationActuator associated with it.
//      navigator.getGamepads()[gamepadIdx]?.vibrationActuator?.playEffect('dual-rumble', {
//        startDelay: 0,
//        duration: 5000, // Moonlight should be sending another rumble event when stopping.
//        weakMagnitude: weakMagnitude,
//        strongMagnitude: strongMagnitude,
//      });
//    }
  }
}
