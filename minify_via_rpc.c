#include "minifyjpeg_clnt.c"
#include "minifyjpeg_xdr.c"
#include "minifyjpeg.h"
#include <stdlib.h>
#include <stdio.h>

CLIENT* get_minify_client(char *server){
    CLIENT *cl;

    /* Your code here */
    if ((cl = clnt_create(server, MINIFY_PROG, MINIFY_VERS, "tcp")) == NULL) {
        printf("Unable to connect to server\n");
        clnt_pcreateerror (server);
        exit(EXIT_FAILURE);
    }

    return cl;
}

/*
The size of the minified file is not known before the call to the library that minimizes it,
therefore this function should allocate the right amount of memory to hold the minimized file
and return it in the last parameter to it
*/
int minify_via_rpc(CLIENT *cl, void *src_val, size_t src_len, size_t *dst_len, void **dst_val){

	/*Your code here */

    image input;
    input.buffer.buffer_len = (u_int)src_len;
    input.buffer.buffer_val = (char *)src_val;

    image output;
    output.buffer.buffer_val = (char *)malloc(src_len * sizeof(char));

    // set the timeout value
    struct timeval tv;
    tv.tv_sec = 7;  // 7 seconds timeout
    tv.tv_usec = 0;
    clnt_control(cl, CLSET_TIMEOUT, (char *)&tv);

    enum clnt_stat rpc_result = minify_image_1(input, &output, cl);
    if (rpc_result != RPC_SUCCESS) {
        clnt_perrno(rpc_result);
        clnt_perror(cl, "Minify_image_1 failed!");
        return rpc_result;
    }

    *dst_len = output.buffer.buffer_len;
    *dst_val = output.buffer.buffer_val;
    return rpc_result;
}
