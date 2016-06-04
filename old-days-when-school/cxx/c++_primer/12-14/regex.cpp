/*
 * regex.cpp - 用正则表达式验证电子邮件地址
 *
 *  C++11标准  STL正则表达式
 *
 *
 *              Copyright  叶剑飞 2012
 *
 * 编译命令：
 *         cl regex.cpp /EHsc /link /out:regex.exe
 *
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <boost/regex.hpp>  // regular expression 正则表达式

using namespace std;
using namespace boost;

int main ( )
{
    string email_address;
    string user_name, domain_name;

    regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");

    // 正则表达式，匹配规则：
    // 第1组（即用户名），匹配规则：0至9、A至Z、a至z、下划线、点、连字符之中
    // 的任意字符，重复一遍或以上
    // 中间，一个“@”符号
    // 第二组（即域名），匹配规则：0至9或a至z之中的任意字符重复一遍或以上，
    // 接着一个点，接着a至z之中的任意字符重复2至3遍（如com或cn等），
    // 第二组内部的一组，一个点，接着a至z之中的任意字符重复2遍（如cn或fr等）
    // 内部一整组重复零次或一次


    // 输入文件结尾符（Windows用Ctrl+Z，UNIX用Ctrl+D）结束循环
    while ( cin >> email_address ) 
    {
        if ( regex_match( email_address, pattern ) )
        {
            cout << "您输入的电子邮件地址合法" << endl;

            // 截取第一组
            user_name = regex_replace( email_address, pattern, string("$1") );

            // 截取第二组
            domain_name = regex_replace( email_address, pattern, string("$2") );

            cout << "用户名：" << user_name << endl;
            cout << "域名：" << domain_name << endl;
            cout << endl;
        }
        else
        {
            cout << "您输入的电子邮件地址不合法" << endl << endl;
        }
    }
    return EXIT_SUCCESS;
}
