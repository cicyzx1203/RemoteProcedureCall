/*
 * Define your service specification in this file and run rpcgen -MN minifyjpeg.x
 */

struct image {
	opaque buffer<>;
};

program MINIFY_PROG {
	version MINIFY_VERS {
		image MINIFY_IMAGE(image) = 1;
	} = 1;
} = 0x31230000;
