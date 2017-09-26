

    export interface RequestData {
        data: any;
        error: (message: Array<string>) => void;
        call: string;
        success: (result: any) => void;

}


    export interface RequestWaitForEach<T> {
        data: (elem:T,index:number) => any;
        error: (message: Array<string>,elem:T,index:number) => void;
        call: string;
        success: (result: any,elem:T,index:number) => void;
        break_on_error: boolean;
    }



    export interface WpfMessage {
        Code: number;
        Call: string;
        Data: any;
        ErrorMessages: Array<string>;
    }


    export class Wpf {
        public alert(): void {
            alert("From The Backend");
        }
        constructor()
        { }

        public IsWpfServerActive(): boolean {
            var external: any = window.external;
            return typeof (external.JavascriptRequest) != "undefined";
        }

        public post(request: RequestData) {
            var value = JSON.stringify(request.data)
            var external: any = window.external;
            var message: WpfMessage;
            if (this.IsWpfServerActive()) {
                var id:string=WpfAjaxManager.Instance.registerRequest(request.call, request.error, request.success);
                var result: boolean = external.JavascriptRequestAsync(request.call, id,value);
                if (!result) {
                    WpfAjaxManager.Instance.cancelRequest(id);
                    console.log("WpfServer entry " + request.call + " not found");
                }
            }
            else {
                alert("WPF Host Application Not Available");
                return;
            }
        }

        public post_wait_for_each<T>(v:Array<T>,request: RequestWaitForEach<T>) {
            var that = this;
            if (v.length == 0)
                return;
            var i = 0;
            var req: RequestData = {
                call: request.call,
                data: request.data(v[i], i),
                error: (m: Array<string>) => {
                    request.error(m, v[i], i);
                    if (request.break_on_error)
                        return;
                    if (i < v.length) {
                        i++;
                        req.data = request.data(v[i], i);
                        this.post(req);
                    }
                },
                success: (result: any) => {
                    request.success(result, v[i], i);
                    if (++i  < v.length) {
                        req.data = request.data(v[i], i);
                        this.post(req);
                    }
                }
            };
            this.post(req);
        }



        postSync(call: string, data: any = null):any {
            var value = JSON.stringify(data)
            var external: any = window.external;
            var message: WpfMessage;
            if (typeof (external.JavascriptRequest) != "undefined") {
                var result: string = external.JavascriptRequest(call, value);
                var message: WpfMessage = <WpfMessage> JSON.parse(result);
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
        }

        postTSync<T>(call: string, data: any = null): T {
            return this.postSync(call, data);
        }


    }

    export class AjaxRequest {
        constructor(public call:string,public onError: (errorMessages:string[]) => void, public onSuccess: (data: any) => void, public requestId: string) {
        }
    };

    export class WpfAjaxManager {
        count: number = 0;
        public requests: Array<AjaxRequest>=[];
        public static Instance: WpfAjaxManager = new WpfAjaxManager();
        public registerRequest(call: string, onError: (errorMessages: string[]) => void, onSuccess: (data: any) => void): string
        {
            var id = (this.count++).toString();

            this.requests[id] = new AjaxRequest(call, onError, onSuccess, id);
            return id;
        }

        public existRequest(requestId: string): boolean {
           return  typeof (this.requests[requestId]) != "undefined"
        }
    
        public cancelRequest(requestId: string) {
            if (this.existRequest(requestId)) {
                delete this.requests[requestId];
            }
        }

        public finishRequest(call: string, requestId: string, data: string) {
           
            var response: WpfMessage = <WpfMessage> JSON.parse(data);

            if (!this.existRequest(requestId)) {
                console.log("Severe error on WpfAjax.finishRequest, request " + requestId + " for call " + call + " not found")
                return;   
            }
            var ajax:AjaxRequest = this.requests[requestId];

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
                    ajax.onError(response.ErrorMessages)
                }
            }
            delete this.requests[requestId];
        }
    }

    export class MoqWpf extends Wpf {
        public static Fixtures: any = [];
        public static Delay: number = 1500;
        public postSync(call: string, data: any = null): any {
            if (typeof (MoqWpf.Fixtures[call]) == "undefined") {
                throw "Route " + call + " Not Found";
            }
            else {
                if (typeof (MoqWpf.Fixtures[call]) == "function")
                    return MoqWpf.Fixtures[call](data);
                else
                    return MoqWpf.Fixtures[call];
            }
        }
        public post(request: RequestData) {
            if (typeof (MoqWpf.Fixtures[request.call]) == "undefined") {
                console.log("Route " + request.call + " Not Found");
                throw "Route " + request.call + " Not Found";
            }
            else {
                var id: string = WpfAjaxManager.Instance.registerRequest(request.call, request.error, request.success);

                if (typeof (MoqWpf.Fixtures[request.call]) == "function") {

                    setTimeout(function () {
                        try {
                            var result = MoqWpf.Fixtures[request.call](request.data);
                            var msg: WpfMessage = {
                                Call: request.call, Code: 201, Data: result, ErrorMessages: null
                            }
                            WpfAjaxManager.Instance.finishRequest(request.call, id, JSON.stringify(msg))
                        }
                        catch (e) {
                            var msg: WpfMessage = {
                                Call: request.call, Code: 503, Data: null, ErrorMessages: [e]
                            }
                            WpfAjaxManager.Instance.finishRequest(request.call, id, JSON.stringify(msg));

                        }
                    }, MoqWpf.Delay);
                }
                else {
                    setTimeout(function () {
                        var msg: WpfMessage = {
                            Call: request.call, Code: 201, Data: MoqWpf.Fixtures[request.call], ErrorMessages: null
                        }
                        WpfAjaxManager.Instance.finishRequest(request.call, id, JSON.stringify(msg));
                    }, 5000);
                }
            }

        }

    }






function WpfFinishRequest(call: string, requestId: string, data: string) {
    WpfAjaxManager.Instance.finishRequest(call, requestId, data);
}