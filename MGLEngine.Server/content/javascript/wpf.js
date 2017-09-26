var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
define(["require", "exports"], function (require, exports) {
    var Wpf = (function () {
        function Wpf() {
        }
        Wpf.prototype.alert = function () {
            alert("From The Backend");
        };
        Wpf.prototype.IsWpfServerActive = function () {
            var external = window.external;
            return typeof (external.JavascriptRequest) != "undefined";
        };
        Wpf.prototype.post = function (request) {
            var value = JSON.stringify(request.data);
            var external = window.external;
            var message;
            if (this.IsWpfServerActive()) {
                var id = WpfAjaxManager.Instance.registerRequest(request.call, request.error, request.success);
                var result = external.JavascriptRequestAsync(request.call, id, value);
                if (!result) {
                    WpfAjaxManager.Instance.cancelRequest(id);
                    console.log("WpfServer entry " + request.call + " not found");
                }
            }
            else {
                alert("WPF Host Application Not Available");
                return;
            }
        };
        Wpf.prototype.post_wait_for_each = function (v, request) {
            var _this = this;
            var that = this;
            if (v.length == 0)
                return;
            var i = 0;
            var req = {
                call: request.call,
                data: request.data(v[i], i),
                error: function (m) {
                    request.error(m, v[i], i);
                    if (request.break_on_error)
                        return;
                    if (i < v.length) {
                        i++;
                        req.data = request.data(v[i], i);
                        _this.post(req);
                    }
                },
                success: function (result) {
                    request.success(result, v[i], i);
                    if (++i < v.length) {
                        req.data = request.data(v[i], i);
                        _this.post(req);
                    }
                }
            };
            this.post(req);
        };
        Wpf.prototype.postSync = function (call, data) {
            if (data === void 0) { data = null; }
            var value = JSON.stringify(data);
            var external = window.external;
            var message;
            if (typeof (external.JavascriptRequest) != "undefined") {
                var result = external.JavascriptRequest(call, value);
                var message = JSON.parse(result);
            }
            else {
                alert("WPF Host Application Not Available");
                return;
            }
            if (message.Code == 404) {
                alert("Route " + call + " Not Found");
            }
            else if (message.Code == 503) {
                throw message.ErrorMessages;
            }
            else {
                return message.Data;
            }
        };
        return Wpf;
    })();
    exports.Wpf = Wpf;
    var AjaxRequest = (function () {
        function AjaxRequest(call, onError, onSuccess, requestId) {
            this.call = call;
            this.onError = onError;
            this.onSuccess = onSuccess;
            this.requestId = requestId;
        }
        return AjaxRequest;
    })();
    exports.AjaxRequest = AjaxRequest;
    ;
    var WpfAjaxManager = (function () {
        function WpfAjaxManager() {
            this.count = 0;
            this.requests = [];
        }
        WpfAjaxManager.prototype.registerRequest = function (call, onError, onSuccess) {
            var id = (this.count++).toString();
            this.requests[id] = new AjaxRequest(call, onError, onSuccess, id);
            return id;
        };
        WpfAjaxManager.prototype.existRequest = function (requestId) {
            return typeof (this.requests[requestId]) != "undefined";
        };
        WpfAjaxManager.prototype.cancelRequest = function (requestId) {
            if (this.existRequest(requestId)) {
                delete this.requests[requestId];
            }
        };
        WpfAjaxManager.prototype.finishRequest = function (call, requestId, data) {
            var response = JSON.parse(data);
            if (!this.existRequest(requestId)) {
                console.log("Severe error on WpfAjax.finishRequest, request " + requestId + " for call " + call + " not found");
                return;
            }
            var ajax = this.requests[requestId];
            if (ajax.call != call) {
                console.log("Severe error on WpfAjax.finishRequest, request call and wpf call do not match " + call + " != " + ajax.call);
                return;
            }
            if (response.Code == 201) {
                if (ajax.onSuccess != null) {
                    ajax.onSuccess(response.Data);
                }
            }
            else {
                if (ajax.onError != null) {
                    ajax.onError(response.ErrorMessages);
                }
            }
            delete this.requests[requestId];
        };
        WpfAjaxManager.Instance = new WpfAjaxManager();
        return WpfAjaxManager;
    })();
    exports.WpfAjaxManager = WpfAjaxManager;
    var MoqWpf = (function (_super) {
        __extends(MoqWpf, _super);
        function MoqWpf() {
            _super.apply(this, arguments);
        }
        MoqWpf.prototype.postSync = function (call, data) {
            if (data === void 0) { data = null; }
            if (typeof (MoqWpf.Fixtures[call]) == "undefined") {
                throw "Route " + call + " Not Found";
            }
            else {
                if (typeof (MoqWpf.Fixtures[call]) == "function")
                    return MoqWpf.Fixtures[call](data);
                else
                    return MoqWpf.Fixtures[call];
            }
        };
        MoqWpf.prototype.post = function (request) {
            if (typeof (MoqWpf.Fixtures[request.call]) == "undefined") {
                console.log("Route " + request.call + " Not Found");
                throw "Route " + request.call + " Not Found";
            }
            else {
                var id = WpfAjaxManager.Instance.registerRequest(request.call, request.error, request.success);
                if (typeof (MoqWpf.Fixtures[request.call]) == "function") {
                    setTimeout(function () {
                        try {
                            var result = MoqWpf.Fixtures[request.call](request.data);
                            var msg = {
                                Call: request.call,
                                Code: 201,
                                Data: result,
                                ErrorMessages: null
                            };
                            WpfAjaxManager.Instance.finishRequest(request.call, id, JSON.stringify(msg));
                        }
                        catch (e) {
                            var msg = {
                                Call: request.call,
                                Code: 503,
                                Data: null,
                                ErrorMessages: [e]
                            };
                            WpfAjaxManager.Instance.finishRequest(request.call, id, JSON.stringify(msg));
                        }
                    }, MoqWpf.Delay);
                }
                else {
                    setTimeout(function () {
                        var msg = {
                            Call: request.call,
                            Code: 201,
                            Data: MoqWpf.Fixtures[request.call],
                            ErrorMessages: null
                        };
                        WpfAjaxManager.Instance.finishRequest(request.call, id, JSON.stringify(msg));
                    }, 5000);
                }
            }
        };
        MoqWpf.Fixtures = [];
        MoqWpf.Delay = 1500;
        return MoqWpf;
    })(Wpf);
    exports.MoqWpf = MoqWpf;
    function WpfFinishRequest(call, requestId, data) {
        WpfAjaxManager.Instance.finishRequest(call, requestId, data);
    }
});
