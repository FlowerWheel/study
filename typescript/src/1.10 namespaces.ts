
namespace NS{
    var str = 'this is a string';
    export function getStr() {
        return str;
    }
    
    export function setStr(s) {
        str = s;
        return str;
    }
}

console.log(NS.getStr());
