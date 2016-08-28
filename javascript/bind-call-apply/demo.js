/**
 * Created by admin on 2015/11/7.
 */

function echo(str){
  console.log(str);
}

var echoHello = echo.bind(null, 'Hello');

echoHello();
