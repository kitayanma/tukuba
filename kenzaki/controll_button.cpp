#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <fstream>
#define JOY_DEV "/dev/input/js0"

using namespace std;

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
//#include "set_controller.h"
int joy_fd( -1 ) , num_of_axis( 0 ) , num_of_buttons( 0 );
char name_of_joystick[80];
vector<char> joy_button;
vector<int> joy_axis;
js_event js;
float button ()
{

	read ( joy_fd , &js , sizeof ( js_event ) );

	switch ( js.type & ~JS_EVENT_INIT ) {
		case JS_EVENT_AXIS:
			joy_axis[( int )js.number] = js.value;
			break;
		case JS_EVENT_BUTTON:
			joy_button[( int )js.number] = js.value;
			//printf("%5d\n %5d\n",( int )js.number,js.value);
			break;
	}
	cout<<"ok"<<endl;
	if ( joy_button[3] == 1 ) {
		cout<<"ok"<<endl;
		return 0;
	}
	else if ( joy_button[14] == 1 ) {
		return 1;
	}
	else if ( joy_button[12] == 1 ) {
		return 2;
	}
	else if ( joy_button[15] == 1 ) {
		return 3;
	}
	else if ( joy_button[13] == 1 ) {
		return 4;
	}
	else {	
		return 5;
	}

}

int main()
{
	float a;
	cout<<"ok"<<endl;
	while(true){
		cout<<"ok"<<endl;
		a=button();
		if(a!=5){
			cout<<a<<endl;
		}
	}
}
