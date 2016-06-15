
var MakePoint: () => {
    x: number;
    y: number;
};

interface Friend {
    name: string;
    favoriteColor?: string
}

function add(friend: Friend) {
    var name = friend.name;
}

add({ name: "Fred" });
add({ name: "Jill", favoriteColor: "green" });
// add({favoriteColor: "blue"}); Error


interface JQuery {
    text(content: string);
}

interface JQuseyStatic {
    get(url: string, callback: (data: string) => any);
    (query: string): JQuery;
}

declare var $: JQuseyStatic;

$.get("", function (data: string) {
    $("div").text(data);
});

var f: { (): string; };
var sameType: () => string = f; // Ok 
// var nope: () => number = sameType; // Error: type mismatch
