#include <at89c5131.h>
#include "serial.h"   

#define idn 6
#define pn 8
#define sn 3

char ch;
int i,j;
unsigned char id[idn] = {"mridul"};
unsigned char password[pn] = {"mrid3933"};
unsigned char input_id[idn] = {"000000"};
unsigned char input_password[pn] = {"00000000"};
unsigned int valid;
unsigned int valid2;
unsigned char input_seed[sn] = {"000"};
unsigned long int seed = 3933;
unsigned char seed_string[sn] = {"000"};
unsigned long int balance = 5000;
unsigned int train_prices[3] = {1500, 1000, 1200};
unsigned char train_no;
unsigned char passenger_count;
unsigned long int total_cost;
unsigned char confirm;
unsigned int timer_count = 0;
bit timer_flag = 0;
bit timeout_occurred = 0;
unsigned long int otp = 0;
unsigned char otp_string[sn] = {"000"};
unsigned char input_otp[sn] = {"000"};
unsigned int otp_valid = 0;

void check();
void output();
void gen_captcha();
void get_captcha();
void check_captcha();
void captcha_output();
void display_trains();
void get_train_selection();
void get_passenger_count();
void calculate_cost();
void payment_confirmation();
void process_payment();
void display_balance();
void gen_otp();
void verify_otp();
void init_timer();
void start_timer();
void timer_isr();
void check_otp_validity();

void int_to_string(unsigned long int val, unsigned char *temp_str_data)
{	
    temp_str_data[0]=48+(val/100);
    temp_str_data[1]=48+((val%100)/10);
    temp_str_data[2]=48+(val%10);
}

void int_to_string_4digit(unsigned long int val, unsigned char *temp_str_data)
{
    temp_str_data[0]=48+(val/1000);
    temp_str_data[1]=48+((val%1000)/100);
    temp_str_data[2]=48+((val%100)/10);
    temp_str_data[3]=48+(val%10);
    temp_str_data[4]='\0';
}

void main(void) {
    uart_init();
    init_timer();
    
    while(1) {
        transmit_string("\n\r Enter Login ID: ");
        for(i=0;i<idn;i++){
            ch = receive_char();
            input_id[i] = ch;
        }
        
        transmit_string("\n\r Enter Password: ");
        for(j=0;j<pn;j++){
            ch = receive_char();
            input_password[j] = ch;
        }

        check();
        output();
        
        if(valid == 1) {
            gen_captcha();
            if(valid2 == 1) {
                display_balance();
                
                display_trains();
                get_train_selection();
                get_passenger_count();
                calculate_cost();
                
                payment_confirmation();
            }
        }
    }
}

void check() {
    for(i=0;i<idn;i++){
        if(input_id[i] == id[i]){valid=1;}
        else {valid=0;break;}
    }

    if(valid==1){
        for(j=0;j<pn;j++){
            if(input_password[j] == password[j]){valid=1;}
            else {valid=0;break;}
        }
    }
}

void output(){
    if(valid==0){
        transmit_string("\r\n Invalid!\r\n");
    }
    else{transmit_string("\r\n Valid!\r\n");}
}

void gen_captcha(){
    long int c1 = 1204;
    long int c2 = 2025;
    int_to_string(seed,seed_string);
    transmit_string("\r\n Captcha: ");
    transmit_string(seed_string);
    seed = ((seed*c1) + c2) % 1000;
    get_captcha();
}

void get_captcha(){
    transmit_string("\r\n Input Captcha: ");
    for(i=0;i<sn;i++){
        ch = receive_char();
        input_seed[i] = ch;
    }
    check_captcha();
}

void check_captcha(){
    for(i=0;i<sn;i++){
        if(input_seed[i] == seed_string[i]){valid2=1;}
        else {valid2=0;break;}
    }
    captcha_output();
}

void captcha_output(){
    if(valid2 == 1){
        transmit_string("\r\n\n Captcha Valid! ");
    }
    else{
        transmit_string("\r\n Invalid! \n");
        gen_captcha();
    }
}

void display_balance() {
    unsigned char bal_str[5];
    int_to_string_4digit(balance, bal_str);
    transmit_string("\r\n\n User wallet balance: Rs. ");
    transmit_string(bal_str);
    transmit_string("\r\n");
}

void display_trains() {
    transmit_string("\r\n Available Trains:");
    transmit_string("\r\n 1 Rajdhani Express - Rs. 1500");
    transmit_string("\r\n 2 Chennai Express - Rs. 1000");
    transmit_string("\r\n 3 Hapa Duronto - Rs. 1200");
    transmit_string("\r\n Enter Train No.: ");
}

void get_train_selection() {
    ch = receive_char();
    train_no = ch - '0'; 
    
    if(train_no < 1 || train_no > 3) {
        transmit_string("\r\n Invalid Train No.\r\n");
        display_trains();
        get_train_selection();
    } else {
        transmit_char(ch);
    }
}

void get_passenger_count() {
    transmit_string("\r\n Enter number of passengers (max 4): ");
    ch = receive_char();
    passenger_count = ch - '0';
    
    if(passenger_count < 1 || passenger_count > 4) {
        transmit_string("\r\n Max. 4 passengers allowed\r\n");
        get_passenger_count();
    } else {
        transmit_char(ch);
    }
}

void calculate_cost() {
    unsigned char cost_str[5];
    total_cost = train_prices[train_no - 1] * passenger_count;
    int_to_string_4digit(total_cost, cost_str);
    
    transmit_string("\r\n Total Cost: Rs. ");
    transmit_string(cost_str);
    transmit_string("\r\n");
}


void payment_confirmation() {
    transmit_string("\r\n Confirm Txn (y/n): ");
    ch = receive_char();
    confirm = ch;
    transmit_char(ch);
    
    if(confirm == 'y') {
        gen_otp();
        start_timer();
        verify_otp();
    } else if(confirm == 'n') {
        transmit_string("\r\n Txn failed\r\n");
        display_trains();
        get_train_selection();
        get_passenger_count();
        calculate_cost();
        payment_confirmation();
    } else {
        transmit_string("\r\n Invalid input\r\n");
        payment_confirmation();
    }
}

void gen_otp() {
    long int c1 = 1204;
    long int c2 = 2025;
    otp = ((seed*c1) + c2) % 1000;
    int_to_string(otp, otp_string);
    transmit_string("\r\n OTP: ");
    transmit_string(otp_string);
    seed = otp;
}

void init_timer() {
    TMOD = 0x01;
    ET0 = 1; 
    EA = 1;
    TH0 = 0x3C;
    TL0 = 0xB0;  
}

void start_timer() {
    timer_count = 0;
    timer_flag = 0;
    timeout_occurred = 0;
    TR0 = 1;
}

void stop_timer() {
    TR0 = 0;
}

void timer0_isr(void) interrupt 1 {
    TH0 = 0x3C;
    TL0 = 0xB0;
    
    timer_count++;
    if(timer_count >= 20) {  
        timer_flag = 1;
        stop_timer();
    }
}

void verify_otp() {
    unsigned char received_char = 0;
    unsigned char otp_index = 0;
    transmit_string("\r\n Enter OTP within 10 seconds: ");
    
    while(1) {
        if(timer_flag) {
            timeout_occurred = 1;
            break;
        }
        
        if(RI) {
            received_char = SBUF;
            RI = 0;
            transmit_char(received_char);
            
            input_otp[otp_index] = received_char;
            otp_index++;
            
            if(otp_index >= 3) {
                break;
            }
        }
    }
    
    stop_timer();
    if(timeout_occurred) {
        transmit_string("\r\n Txn failed: Timeout\r\n");
        payment_confirmation();
        return;
    }
    
    check_otp_validity();
}

void check_otp_validity() {
    for(i=0; i<sn; i++) {
        if(input_otp[i] == otp_string[i]) {
            otp_valid = 1;
        } else {
            otp_valid = 0;
            break;
        }
    }
    
    if(otp_valid) {
        process_payment();
    } else {
        transmit_string("\r\n Txn failed: Invalid OTP\r\n");
        payment_confirmation();
    }
}

void process_payment() {
    if(balance < total_cost) {
        transmit_string("\r\n Txn failed: Insufficient Balance\r\n");
        display_trains();
        get_train_selection();
        get_passenger_count();
        calculate_cost();
        payment_confirmation();
    } else {
        balance = balance - total_cost;
        transmit_string("\r\n Booking Successful\r\n");
        display_balance();
        valid = 0;
        valid2 = 0;
    }
}