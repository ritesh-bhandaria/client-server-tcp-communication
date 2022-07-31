#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(){
    //CLIENT SOCKET CODE BY 20BCS183 RITESH BHANDARIA
    //creates a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    //specify an  address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    //check for error with the connection
    if(connection_status==-1){
        printf("there is some error connecting to the remote socket \n\n");
        return 0;
    } 

    //get the values and operations from the user
    int op;
    float num1,num2;
    printf("please use the corresponding number for the operation \n --------\n");
    printf("1 \tadd \n2 \tsubtract \n3 \tmultiply \n4 \tdivide \n5 \texp \n6 \tpercent \n7 \tlog \n8 \tsin \n9 \tcos \n10 \ttan \n ---------\n");
    printf("enter number1 : ");
    scanf("%f",&num1);
    printf("enter operation : ");
    scanf("%d",&op);
    if(op<=7){
        printf("enter number2 : ");
        scanf("%f",&num2);
    }

    //send the data to server
    write(network_socket,&num1,sizeof(num1));
    write(network_socket,&op,sizeof(op));
    if(op<=7)
    {
        write(network_socket,&num2,sizeof(num2));
    }
    //recieve data from the server
    char server_response[250];
    float res;
    recv(network_socket, &server_response, sizeof(server_response), 0);
    recv(network_socket,&res,sizeof(res),0);
    //print received data
    printf("server sent thet following message:\n %s\n",server_response);
    printf("this is the requested solution : %f\n",res);


    //close the socket
    close(network_socket);
    return 0;
}