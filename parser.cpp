#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <stdio.h>
#include <ctype.h>
#include <utility>
#include "graphics.h"
using namespace std;


class Parser{

public:
vector<pair<string, string>> tokenlist;
 int pointer;
 //string token;
 int x,y;
 
 
 string gettoken(){
	 return this->tokenlist[pointer].first;
 }
 string getnexttoken(){
	 string token =tokenlist[pointer+1].first;
	  pointer++;
	  return token;
}
 string checknexttoken(){
	 string token =tokenlist[pointer+1].first;
	 
	  return token;
}
 string gettokentype(){
	 return this->tokenlist[pointer].second;
 }
bool match(string type){
	if(this->gettoken()==type){
		if(this->pointer!= this->tokenlist.size()-1){
			this->getnexttoken();
		}
		return true;
	}
	else{
		cout<<"Error::token missmatch "<<this->gettoken()<<endl;
		return false;
	}
 }
bool matchtype(string type){
	if(this->gettokentype() ==type){
		this->getnexttoken();
		//cout<<this->pointer<<endl;
		return true;
	}
	else{
		cout<<"Error::token missmatch "<<this->gettokentype()<<endl;
		return false;
	}
 }
void drawstmt(){
	//this->x -35,this->y -35,this->x +35,this->y +35
	rectangle(this->x -35,this->y -25,this->x +35,this->y +25);

}
void lineafterstmt(){
	line(this->x +35,y,this->x +250,y);
	this->x = this->x + 285;
}
void update_xy(int w,int z){
	this->x = w;
	this->y = z;
}

void drawop(int w,int z){
	fillellipse(w,z,40,20);
	//outtextxy(w-15, z,"op");
}
void drawid_num(int w,int z){
	fillellipse(w,z,40,20);
	outtextxy(w-15, z,"num/id");
}

void drawwrite(){
	string token=this->gettoken();
	string tokentype=this->gettokentype();
	if(token == "if"){
	
		outtextxy(x-15, y-15,"if");
	}else if(token == "read"){
		string token = this->checknexttoken();
		char *ct = new char[token.length() + 1];
		strcpy(ct, token.c_str());
		outtextxy(x-15, y-15,"read");
		outtextxy(x-15, y,ct);
	}else if(token == "write"){
		outtextxy(x-15, y-15,"write");
	}else if(tokentype == "identifier"){
		string token = this->gettoken();
		char *ct = new char[token.length() + 1];
		strcpy(ct, token.c_str());
		outtextxy(x-15, y-15,"assign");
		outtextxy(x-15, y,ct);
	}else if(token == "repeat"){
		outtextxy(x-15, y-15,"repeat");
	}
	
}
void stmt_sequence(){
	drawstmt();
	statement();
	while(this->gettoken()==";"){
		lineafterstmt();
		match(";");
		drawstmt();
		statement();
	}
	cout << "stmt-seq" <<endl;
}
void statement(){
	//drawstmt();
	if(this->gettoken()=="if"){
		if_stmt();
	}
	else if(this->gettoken()=="repeat"){
		repeat_stmt();
	}
	else if(this->gettoken()=="read"){
		read_stmt();
	}
	else if(this->gettoken()=="write"){
		write_stmt();
	}
	else if(this->gettokentype()=="identifier"){
		assign_stmt();
	}
	else{cout<<"Error::statement missmatch "<<this->gettoken()<<endl;}
}
void if_stmt(){
		int w=  this->x-20 ;int z=  this->y+35 ;
		int oldx=this->x;int oldy= this->y;
		int q=  this->x+75 ;int t=  this->y+200 ;
		drawwrite();
		match("if");
		update_xy(w,z);
		exp(w,z);
		update_xy(oldx,oldy);
		match("then");
		update_xy(q,t);
		setcolor(5);
		line(oldx,oldy+20,q,t-20);
		setcolor(15);
		stmt_sequence();
		update_xy(oldx,oldy);
		
		if(this->gettoken()=="else"){
			match("else");
			update_xy(q,t);
			stmt_sequence();
			update_xy(oldx,oldy);
		}
		match("end");
    cout <<"if-stmt"<<endl;
}
void repeat_stmt(){
	int w=  this->x ;int z=  this->y+35 ;
	int oldx=this->x;int oldy= this->y;
	int q=  this->x+75 ;int t=  this->y+200 ;
	drawwrite();
	match("repeat");
	update_xy(q,t);
	setcolor(5);
	line(oldx,oldy+20,q,t-20);
	setcolor(15);
	stmt_sequence();
	update_xy(oldx,oldy);
	match("until");
	update_xy(w,z);
	exp(w,z);
	update_xy(oldx,oldy);
	//line(oldx,oldy+20,w,t-20);
	cout << "repeat-stmt" <<endl;
}
void read_stmt(){
	drawwrite();
	match("read");
	matchtype("identifier");
	cout << "read-stmt" <<endl;
}
void write_stmt(){
	int oldx=  this->x ;int oldy=  this->y ;
	int w=  this->x ;int z=  this->y+35 ;
	drawwrite();
	match("write");
	exp(oldx,oldy);
	cout << "write-stmt" <<endl;
}
void assign_stmt(){
	int oldx=  this->x ;int oldy=  this->y;
	int w=this->x;int z=  this->y+35;
	drawwrite();
	matchtype ("identifier");
	match (":=");
	//drawexp(this->x,this->y +50);
	update_xy(w,z);
	exp(oldx,oldy);
	update_xy(oldx,oldy);
	cout << "assign-stmt" <<endl;
}
void exp(int oldxx,int oldyy){
	int oldx=this->x;int oldy= this->y;
	int w=  this->x -50 ;int z=  this->y+50 ;
	update_xy(w,z);
	setcolor(10);
	line(this->x,this->y,oldx,oldy);
	setcolor(15);
	simple_exp(oldx,oldy);
	update_xy(oldx,oldy);
	if (this->gettoken()=="<"||this->gettoken()=="="){

		string token= this->gettoken();
		char *ct = new char[token.length() + 1];
		strcpy(ct, token.c_str());
		circle(this->x+15,this->y,25);
		setcolor(10);
		line(this->x+10,this->y-10,oldxx,oldyy);
		setcolor(15);
		outtextxy(this->x+5,this->y-10,ct);
		//drawid_num( this->x+50,this->y+100);
		comparison_op();
		int w=  this->x+50 ;int z=  this->y+50 ;
		update_xy(w,z);
		simple_exp(oldx,oldy);
		update_xy(oldx,oldy);
		setcolor(10);
		line(w,z,oldx,oldy);
		setcolor(15);
	}
	//cout << "exp" <<endl;
}
void simple_exp(int oldxx,int oldyy){
	int oldx=this->x;int oldy= this->y;
	int w=  this->x -50 ;int z=  this->y+50 ;
	update_xy(w,z);
		setcolor(10);
	line(this->x,this->y,oldx,oldy);
	setcolor(15);
	term(oldx,oldy);
	update_xy(oldx,oldy);
	if (this->gettoken()=="+"||this->gettoken()=="-"){
		string token= this->gettoken();
		char *ct = new char[token.length() + 1];
		strcpy(ct, token.c_str());
		circle(this->x+10,this->y,25);
		setcolor(10);
		line(this->x,this->y,oldxx,oldyy);
		setcolor(15);
		outtextxy(this->x+5,this->y-10,ct);
		addop();
		int w=  this->x+50 ;int z=  this->y+50 ;
		update_xy(w,z);
		term(oldx,oldy);
		update_xy(oldx,oldy);
		setcolor(10);
		line(w,z,oldx,oldy);
		setcolor(15);;
	}
	//cout << "simple_exp" <<endl;
}
void comparison_op(){
	if(this->gettoken() == "="){
		match("=");
	}else if(this->gettoken() == "<"){
			//cout << "<" <<endl;
			match("<");
	}else{
			cout << "Expected < or = but found none." << endl;
	}
}
void addop(){
	if(this->gettoken() == "+"){
		match("+");//cout<<"addop+"<<endl;
	}else if(this->gettoken() == "-"){
		match("-");//cout<<"addop-"<<endl;
	}else{
			cout << "Expected + or - but found none." << endl;
	}
	
}
void term(int oldxx,int oldyy){
	int oldx=this->x;int oldy= this->y;
	int w=  this->x -50 ;int z=  this->y+25 ;
	update_xy(w,z);
		setcolor(10);
	line(this->x,this->y,oldx,oldy);
	setcolor(15);
	factor(oldx,oldy);
	update_xy(oldx,oldy);
	if (this->gettoken()=="*"||this->gettoken()=="/"){
		string token= this->gettoken();
		char *ct = new char[token.length() + 1];
		strcpy(ct, token.c_str());
		circle(this->x+10,this->y,25);
			setcolor(10);
		line(this->x,this->y,oldx,oldy);
		setcolor(15);
		outtextxy(this->x+5,this->y-10,ct);
		mulop();
		int w=  this->x+50 ;int z=  this->y+25 ;
		update_xy(w,z);
		factor(oldx,oldy);
		update_xy(oldx,oldy);
				setcolor(10);
		line(w,z,oldx,oldy);
		setcolor(15);

	}
	//cout << "term" <<endl;
}
void mulop(){
	if(this->gettoken() == "*"){
		match("*");
	}else if(this->gettoken() == "/"){
		match("/");
	}else{
			cout << "Expected * or / but found none." << endl;
	}
}
void factor(int oldxx,int oldyy){
	int oldx=this->x;int oldy= this->y;


	if(this->gettoken()=="("){
		match("(");
		exp(oldx,oldy);
		match(")");
	}
	else if(this->gettokentype()=="identifier") {
		string token= this->gettoken();
		char *ct = new char[token.length() + 1];
		strcpy(ct, token.c_str());
		circle(this->x,this->y,25);
		setcolor(10);
		line(this->x,this->y,oldx,oldy);
		setcolor(15);
		outtextxy(this->x+5,this->y-10,ct);
		delete [] ct;
		matchtype("identifier");
		//cout<<"identifier"<<endl;
	}
	else if(this->gettokentype()=="number") {
		string token= this->gettoken();
		char *ct = new char[token.length() + 1];
		strcpy(ct, token.c_str());
		//delete [] ct;
		//char msg[];
		//
		//sprintf(msg, "%S", token);
		circle(this->x,this->y,25);
		setcolor(10);
		line(this->x,this->y,oldx,oldy);
		setcolor(15);
		outtextxy(this->x+5,this->y-10,ct);
		delete [] ct;
		matchtype("number");
		//cout<<"number"<<endl;
	}
}



};


void main(){
	
vector<pair<string, string>> tokens;
tokens.push_back(std::make_pair("read","RW"));tokens.push_back(std::make_pair("x","identifier"));tokens.push_back(std::make_pair(";","sym"));
tokens.push_back(std::make_pair("if","RW"));tokens.push_back(std::make_pair("0","number"));tokens.push_back(std::make_pair("<","sym"));tokens.push_back(std::make_pair("x","identifier"));
tokens.push_back(std::make_pair("then","RW"));tokens.push_back(std::make_pair("fact","identifier"));tokens.push_back(std::make_pair(":=","assigment"));tokens.push_back(std::make_pair("1","number"));tokens.push_back(std::make_pair(";","sym"));
tokens.push_back(std::make_pair("repeat","RW"));tokens.push_back(std::make_pair("fact","identifier"));tokens.push_back(std::make_pair(":=","assigment"));tokens.push_back(std::make_pair("fact","identifier"));tokens.push_back(std::make_pair("*","sym"));tokens.push_back(std::make_pair("x","identifier"));tokens.push_back(std::make_pair(";","sym"));
tokens.push_back(std::make_pair("x","identifier"));tokens.push_back(std::make_pair(":=","assigment"));tokens.push_back(std::make_pair("x","identifier"));tokens.push_back(std::make_pair("-","sym"));tokens.push_back(std::make_pair("1","number"));
tokens.push_back(std::make_pair("until","RW"));tokens.push_back(std::make_pair("x","identifier"));tokens.push_back(std::make_pair("=","sym"));tokens.push_back(std::make_pair("0","number"));tokens.push_back(std::make_pair(";","sym"));
tokens.push_back(std::make_pair("write","RW"));tokens.push_back(std::make_pair("fact","identifier"));tokens.push_back(std::make_pair("end","RW"));


Parser p;
p.tokenlist= tokens;
p.pointer=0;
p.x=200;
p.y=100;



initwindow(10000, 10000, "Parse tree");

p.stmt_sequence();

    while (!kbhit( ))
    {
        delay(200);
    }

}