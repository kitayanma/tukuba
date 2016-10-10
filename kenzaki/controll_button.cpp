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

	int joy_fd( -1 ) , num_of_axis( 0 ) , num_of_buttons( 0 );
	char name_of_joystick[80];
	vector<char> joy_button;
	vector<int> joy_axis;

	if ( ( joy_fd = open( JOY_DEV, O_RDONLY ) ) < 0 ) {
//		printf( "Failed to open %s" ,JOY_DEV );
		cerr << "Failed to open " << JOY_DEV << endl;
		return -1;
	}

	ioctl( joy_fd , JSIOCGAXES , &num_of_axis );
	ioctl( joy_fd , JSIOCGBUTTONS , &num_of_buttons );
	ioctl( joy_fd , JSIOCGNAME(80) , &name_of_joystick );

	joy_button.resize( num_of_buttons , 0 );
	joy_axis.resize( num_of_axis , 0 );

//	printf( "Joystick: %s axis: %d buttons: %d\n" ,name_of_joystick ,num_of_axis ,num_of_buttons );

	fcntl( joy_fd, F_SETFL, O_NONBLOCK ); // using non-blocking mode

//	if ( check_apm() ) {
//		return 1;
//	}

	for ( int i = 0 ; i < 10000 ; i++ ) {
		imuLoop();
		usleep( 1000 );
		if( i % 1000 == 0 ) {
			printf( "#" );
			fflush( stdout );
		}
	}

	for ( int i = 0 ; i < 4 ; i++ ) {
		if ( !pwm.init( i ) ) {
			fprintf( stderr , "Output Enable not set. Are you root?\n" );
			return 0;
		}
		pwm.enable( i );
		pwm.set_period( i , 500 );
	}

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
		a=button ();
		if(a!=5){
			cout<<a<<endl;
		}
	}
}
