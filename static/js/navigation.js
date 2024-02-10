const hoveredClassName = 'hovered';

function unmarkElementById(id) {
  unmarkElement(document.getElementById(id));
}

function unmarkElement(element) {
  if (element) {
    element.classList.remove(hoveredClassName);
    element.dispatchEvent(new Event('mouseleave'));
  }
}

function markElementById(id) {
  markElement(document.getElementById(id));
}

function markElement(element) {
  if (element) {
    element.classList.add(hoveredClassName);
    element.dispatchEvent(new Event('mouseenter'));
  }
}

function mark(value) {
  if (typeof value === 'string') {
    markElementById(value);
  } else if (typeof value === 'object') {
    markElement(value);
  }
}

function unmark(value) {
  if (typeof value === 'string') {
    unmarkElementById(value);
  } else if (typeof value === 'object') {
    unmarkElement(value);
  }
}

function isPopupActive(id) {
  return document
    .getElementById(id)
    .parentNode
    .children[1]
    .classList
    .contains('is-visible');
}
class ListView {
  constructor(func) {
    this.index = 0;
    this.func = func;
  }

  prev() {
    if (this.index > 0) {
      const array = this.func();
      unmark(array[this.index]);
      --this.index;
      mark(array[this.index]);
    } 
  }

  next() {
    const array = this.func();
    if (this.index < array.length - 1) {
      unmark(array[this.index]);
      ++this.index;
      mark(array[this.index]);
    } 
  }
  
  setIndex(index) {
    const array = this.func();
    if (index >= 0 && index < array.length - 1) {
      this.index = index;
    }
  }

  current() {
    return this.func()[this.index];
  }
};

const Views = {
  Hosts: {
    view: new ListView(() => document.getElementById('host-grid').children),
    up: function () {
      Navigation.change(Views.HostsNav);
    },
    left: function () {
      this.view.prev();
    },
    right: function () {
      this.view.next();
    },
    accept: function () {
      const element = this.view.current();
      if (element.id === 'addHostCell') {
        element.click();
      } else {
        element.children[0].click();
      }
    },
    back: function () {
      var modal = document.querySelector('#quitMoonlight');
      modal.showModal();
      Navigation.push(Views.QuitMoonlightDialog);
    },
    enter: function () {
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
  HostsNav: {
    view: new ListView(() => [
      'selectResolution',
      'selectFramerate',
      'bitrateField',
      'externalAudioBtn',
      'optimizeGamesBtn']),
    left: function () {
      this.view.prev();
    },
    right: function () {
      this.view.next();
    },
    down: function () {
      Navigation.change(Views.Hosts);
    },
    accept: function () {
      document.getElementById(this.view.current()).click();
    },
    back: function () {
      var modal = document.querySelector('#quitMoonlight');
      modal.showModal();
      Navigation.push(Views.QuitMoonlightDialog);
    },
    enter: function () {
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
  QuitMoonlightDialog: {
    view: new ListView(() => [
      'continueQuitMoonlight',
      'cancelQuitMoonlight']),
    left: function () {
      this.view.prev();
    },
    right: function () {
      this.view.next();
    },
    accept: function () {
      document.getElementById(this.view.current()).click();
    },
    back: function () {
      document.getElementById('cancelQuitMoonlight').click();
    },
    enter: function () {
      this.view.setIndex(1);
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
  AddHostDialog: {
    view: new ListView(() => [
      'dialogInputHost',
      'continueAddHost',
      'cancelAddHost']),
    left: function () {
      this.view.prev();
    },
    right: function () {
      this.view.next();
    },
    down: function () {
      document.getElementById('continueAddHost').click();
    },
    accept: function () {
      document.getElementById(this.view.current()).click();
    },
    back: function () {
      document.getElementById('cancelAddHost').click();
    },
    enter: function () {
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
  DeleteHostDialog: {
    view: new ListView(() => [
      'continueDeleteHost',
      'cancelDeleteHost']),
    left: function () {
      this.view.prev();
    },
    right: function () {
      this.view.next();
    },
    down: function () {
      document.getElementById('continueDeleteHost').click();
    },
    accept: function () {
      document.getElementById(this.view.current()).click();
    },
    back: function () {
      document.getElementById('cancelDeleteHost').click();
    },
    enter: function () {
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
  SelectResolutionMenu: {
    isActive: () => isPopupActive('resolutionMenu'),
    view: new ListView(
      () => document
        .getElementById('resolutionMenu')
        .parentNode
        .children[1]
        .children[1]
        .children),
    up: function () {
      this.view.prev();
    },
    down: function () {
      this.view.next();
    },
    accept: function () {
      this.view.current().click();
    },
    back: function () {
      document.getElementById('selectResolution').click();
    },
    enter: function () {
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
  SelectFramerateMenu: {
    isActive: () => isPopupActive('framerateMenu'),
    view: new ListView(
      () => document
        .getElementById('framerateMenu')
        .parentNode
        .children[1]
        .children[1]
        .children),
    up: function () {
      this.view.prev();
    },
    down: function () {
      this.view.next();
    },
    accept: function () {
      this.view.current().click();
    },
    back: function () {
      document.getElementById('selectFramerate').click();
    },
    enter: function () {
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
  SelectBitrateMenu: {
    isActive: () => isPopupActive('bandwidthMenu'),
    left: function () {
      bitrateSlider.stepDown();
      bitrateSlider.dispatchEvent(new Event('input'));
    },
    right: function () {
      bitrateSlider.stepUp();
      bitrateSlider.dispatchEvent(new Event('input'));
    },
    accept: function () {
      document.getElementById('bandwidthMenu').click();
    },
    back: function () {
      document.getElementById('bandwidthMenu').click();
    },
    enter: function () { },
    leave: function () { },
  },
  PairingDialog: {
    view: new ListView(() => ['cancelPairingDialog']),
    accept: function () {
      document.getElementById(this.view.current()).click();
    },
    back: function () {
      document.getElementById('cancelPairingDialog').click();
    },
    enter: function () {
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    }
  },
  Play: {
    view: ['nacl_module'],
    back: function () {
      sendMessage('stopRequest', []).then(function () {
        Navigation.pop();
        api.refreshServerInfo().then(function (ret) {
          // Return to app list with new currentgame
          showApps(api);
        }, function () {
          // Return to app list anyway
          showApps(api);
        })
      }, function () { });
    },
    enter: function () {
    },
    leave: function () {
    }
  },
  Apps: {
    view: new ListView(() => document.getElementById('game-grid').children),
    up: function () {
      Navigation.change(Views.AppsNav);
    },
    left: function () {
      this.view.prev();
    },
    right: function () {
      this.view.next();
    },
    accept: function () {
      this.view.current().click();
    },
    back: function () {
      document.getElementById('backIcon').click();
    },
    enter: function () {
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
  AppsNav: {
    view: new ListView(() => [
      'backIcon',
      'quitCurrentApp']),
    down: function () {
      Navigation.change(Views.Apps);
    },
    left: function () {
      this.view.prev();
    },
    right: function () {
      this.view.next();
    },
    accept: function () {
      document.getElementById(this.view.current()).click();
    },
    back: function () {
      document.getElementById('backIcon').click();
    },
    enter: function () {
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
  CloseAppDialog: {
    view: new ListView(() => [
      'continueQuitApp',
      'cancelQuitApp']),
    down: function () {
      Navigation.change(Views.Apps);
    },
    left: function () {
      this.view.prev();
    },
    right: function () {
      this.view.next();
    },
    accept: function () {
      document.getElementById(this.view.current()).click();
    },
    back: function () {
      document.getElementById('cancelQuitApp').click();
    },
    enter: function () {
      this.view.setIndex(1);
      mark(this.view.current());
    },
    leave: function () {
      unmark(this.view.current());
    },
  },
};

const Navigation = (function () {
  let hasFocus = false;

  function loseFocus() {
    if (hasFocus) {
      hasFocus = false;
      Stack.get().leave();
    }
  }

  function focus() {
    if (!hasFocus) {
      hasFocus = true;
      Stack.get().enter();
    }
  }
  function runOp(name) {
    return () => {
      common.logMessage("Nav op called: " + name);
      if (!State.isRunning()) {
        return;
      }

      if (!hasFocus) {
        focus();
        return;
      }
      const view = Stack.get();
      if (view[name]) {
        view[name]();
      }
    };
  }

  const Stack = (function () {
    const viewStack = [];

    function push(view) {
      if (get()) {
        get().leave();
      }
      viewStack.push(view);
      get().enter();
    }

    function change(view) {
      get().leave();
      viewStack[viewStack.length - 1] = view;
      get().enter();
    }

    function pop() {
      if (viewStack.length > 1) {
        get().leave();
        viewStack.pop();
        get().enter();
      }
    }

    function get() {
      return viewStack[viewStack.length - 1];
    }

    return { get, push, change, pop };
  })();

  const State = (function () {
    let running = false;

    function start() {
      if (!running) {
        running = true;
        window.addEventListener('mousemove', loseFocus);
      }
    }

    function stop() {
      if (running) {
        running = false;
        window.removeEventListener('mousemove', loseFocus);
      }
    }

    function isRunning() {
      return running;
    }

    return { start, stop, isRunning };
  })();

  return {
    accept: runOp('accept'),
    back: runOp('back'),
    left: runOp('left'),
    right: runOp('right'),
    up: runOp('up'),
    down: runOp('down'),
    push: Stack.push,
    change: Stack.change,
    pop: Stack.pop,
    start: State.start,
    stop: State.stop,
  };
})();
