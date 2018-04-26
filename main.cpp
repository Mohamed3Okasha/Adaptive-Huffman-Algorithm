#include <iostream>
#include "Tree.h"
#include <map>
#include <cmath>
using namespace std;

string convertToBinary(int, int);
int convertToDecimal(string);
string compress(char[], int, string);
string decompress(char[], int, string);
string readFromString(string, int, int);

string sharedBC, input;

int main(){

    char arr[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u', 'v','w','x','y','z'};
    //char arr[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    string str = compress(arr, 26, "lossy");
    cout << str << endl;
    cout << decompress(arr, 26, str) << endl;
    return 0;
}
//function for converting from decimal to binary
//length is the number of bits to represent the integer
string convertToBinary(int n, int length){
    string str = "";
    while(n){
        //get the bit and convert it to char
        str = char((n % 2) + '0') + str;
        n /= 2;
    }
    int strlen = (int) str.length();
    //if the string length after converting to binary less than length
    if(strlen < length){
        //append '0' to the start of the string
        for(int i = 0; i < length - strlen; ++i){
            str = '0' + str;
        }
    }
    return str;
}
//function for encoding
//the character set and the length of it is passed to the function
string compress(char charSet[], int charSetLength, string str){
    map<char, int> index;
    for(int i = 0; i < charSetLength; ++i){
        index[charSet[i]] = i + 1;
    }
    int e = log2(charSetLength);
    int r = charSetLength %  (int) pow(2, e);
    Tree tree;
    string encoding = "";
    //loop through every character
    for(int i = 0; i < (int) str.length(); ++i){
        int k = index[str[i]];
        //encode every character Comp()
        Node* node = tree.findNode(str[i]);
        if(!node){
            string fx;
            if(k <= 2*r){
                fx = convertToBinary(k-1, e+1);
            }
            else{
                fx = convertToBinary(k-r-1, e);
            }
            encoding += tree.getNYTCode() + fx;
            tree.insertNode(str[i]);
        }
        else{
            ++node->weight;
            encoding += tree.getCharCode(node);
        }
        tree.updateWeight();
        tree.checkAndSwap();
    }
    return encoding;
}
//function for converting from binary to decimal
int convertToDecimal(string binary){
    int decimal = 0;
    int length = (int) binary.length();
    int shift = length - 1;
    for(int i = 0; i < length; ++i){
        decimal |= (binary[i] - '0') << shift;
        --shift;
    }
    return decimal;
}

//function for decoding
//the character set and the length of it is passed to the function
string decompress(char charSet[], int charSetLength, string str){
    map<int, char> index;
    for(int i = 0; i < charSetLength; ++i){
        index[i + 1] = charSet[i];
    }
    int e = log2(charSetLength);
    int r = charSetLength %  (int) pow(2, e);
    Tree tree;
    //the position that we will read the date starting from it
    int position = 0;
    string decoding = "";
    int decimal = convertToDecimal(readFromString(str, position, e));
    if(decimal <= r){
        decimal = convertToDecimal(readFromString(str, position, e+1));
        decoding += index[decimal + 1];
        position += (e + 1);
        tree.insertNode(index[decimal + 1]);
    }
    else{
        decoding += index[decimal + r + 1];
        position += e;
        tree.insertNode(index[decimal + r + 1]);
    }
    tree.updateWeight();
    tree.checkAndSwap();
    int i;
    while(position < (int) str.length()){
        i = 1;
        string binary = readFromString(str, position, i);
        Node* node = tree.getNodeByBinary(binary);
        while(!tree.isLeaf(node)){
            ++i;
            binary = readFromString(str, position, i);
            node = tree.getNodeByBinary(binary);
        }
        if(binary == tree.getNYTCode()){
            position += i;
            decimal = convertToDecimal(readFromString(str, position, e));
            if(decimal <= r){
                decimal = convertToDecimal(readFromString(str, position, e+1));
                decoding += index[decimal + 1];
                position += (e + 1);
                tree.insertNode(index[decimal + 1]);
            }
            else{
                decoding += index[decimal + r + 1];
                position += e;
                tree.insertNode(index[decimal + r + 1]);
            }
        }
        else{
            decoding += node->value;
            ++node->weight;
            position += i;
        }
        tree.updateWeight();
        tree.checkAndSwap();
    }
    return decoding;
}
string readFromString(string str, int start, int length){
    string newStr = "";
    for(int i = start; i < start + length && i < (int) str.length(); ++i){
        newStr += str[i];
    }
    return newStr;
}
