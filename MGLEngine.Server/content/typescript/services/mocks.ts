import { InMemoryWebApiModule, InMemoryDbService } from 'angular-in-memory-web-api';

export class InMemMockService implements InMemoryDbService {

    static Fixture: { [typeName: string]: string } = {};

    createDb() {
        //Deep copy
        var str = JSON.stringify(InMemMockService.Fixture);
        var result = JSON.parse(str);

        //return result
        return result;
    }



    parseUrl(url: string): any {
        var t = url.trim();
        t = t.replace("http://", "");
        t = t.replace("https://", "");

        var query = ""
        if (t.indexOf("?") != -1) {
            query = t.substring(t.indexOf("?") + 1);
            t = t.substring(0, t.indexOf('?'))
        }
        var urlParts = t.split("/");
        var collection = "";



        for (var i = 0; i < urlParts.length - 1; i++) {
            collection += urlParts[i] + "_";
        }
        collection += urlParts[i];

        return {
            base: "",
            collectionName: collection,
            id: "",
            query: query
        };
    }


    static AddFixture(collection: string, data: any): void {
        InMemMockService.Fixture[collection] = data;
    }

}
