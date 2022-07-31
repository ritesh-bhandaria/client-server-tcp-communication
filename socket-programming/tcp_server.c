#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <math.h>
#include <netinet/in.h>

int main(){
    //SERVER SOCKET CODE BY 20BCS183 RITESH BHANDARIA
    char server_message[250] = "congratulations! you have reached the server";

    //CREATE A SERVER SOCKET 
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //bind thesocket to specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 5);
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    //get some values from client
    float num1,num2;
    int op;
    read(client_socket,&num1,sizeof(num1));
    printf("received data: %f \n",num1);
    read(client_socket,&op,sizeof(op));
    printf("received operation: %d \n",op);
    if(op<=7){
        read(client_socket,&num2,sizeof(num2));
         printf("received data: %f \n",num2);
    }

    //evaluate the result
    float result;
    if(op==1){
        result=num1+num2;
    }
    else if(op==2){
        result=num1-num2;
    }
    else if(op==3){
        result=num1*num2;
    }
    else if(op==4){
        result=num1/num2;
    }
    else if(op==5){
        result=pow(num1,num2);
    }
    else if(op==6){
        result=log(num1);
    }
    else if(op==7){
        result=(num1/num2)*100;
    }
    else if(op==8){
        result=sin(num1);
    }
    else if(op==9){
        result=cos(num1);
    }
    else if(op==10){
        result=tan(num1);
    }

    //send the results
    send(client_socket, server_message, sizeof(server_message), 0);
    send(client_socket,&result,sizeof(result),0);

    //CLOSE SERVER SOCKET
    close(server_socket);
    return 0;
}