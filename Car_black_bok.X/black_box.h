/* 
 * File:   black_box.h
 * Author: mdfai
 *
 * Created on 27 September, 2023, 9:40 PM
 */

#ifndef BLACK_BOX_H
#define	BLACK_BOX_H

#define DASHBOARD               1
#define PASSWORD                2
#define LOGIN_SCREEN            3
#define VIEW_LOG                4
#define DOWNLOAD_LOG            5
#define CLEAR_LOG               6
#define SET_TIME                7
#define CHANGE_PSSD             8


void display(unsigned char *event,unsigned char speed);
unsigned char check_pssd(unsigned char key);
unsigned char login_screen(unsigned char key);
void log_event(unsigned char *event,unsigned char speed);
void download_log();
unsigned char set_time(unsigned char key);
void get_time();

#endif	/* BLACK_BOX_H */

