#include <stdio.h>

#include "magickminify.h"
#include "minifyjpeg.h"

/* Implement the server-side functions here */

bool_t minify_image_1_svc(image input, image *output, struct svc_req *req) {
    ssize_t output_len;

    magickminify_init();

    output->buffer.buffer_val = magickminify(input.buffer.buffer_val, input.buffer.buffer_len, &output_len);

    output->buffer.buffer_len = (u_int)output_len;

    return TRUE;
}

int minify_prog_1_freeresult(SVCXPRT *svcxprt, xdrproc_t xdr_proc, caddr_t xdr_caddr) {
    magickminify_cleanup();
    xdr_free(xdr_proc, xdr_caddr);
    return 1;
}
