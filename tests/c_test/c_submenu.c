/*
 * submenu.c - A test program for the libcmdf library
 * Public domain; no warrenty applied, use at your own risk!
 * Authored by Rull Deef, 2020.
 *
 * License:
 * --------
 * This software is dual-licensed to the public domain and under the following license: 
 * you are granted a perpetual, irrevocable license to copy, modify, 
 * publish and distribute this file as you see fit.
 */

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL
#include "libcmdf.h"

#include <stdio.h>

#define PROG_INTRO "submenu - A simple test program with submenu for libcmdf.\n" \
                   "You can use this as a reference on how to use the library!"

#define SUBMENU_INTRO "This is a submenu!"

static CMDF_RETURN do_hello(cmdf_arglist *arglist)
{
    printf("\nHello, world!\n");
    return CMDF_OK;
}

static CMDF_RETURN do_printargs(cmdf_arglist *arglist)
{
    int i;

    if (!arglist)
    {
        printf("\nNo arguments provided!\n");
        return CMDF_OK;
    }

    printf("\nTotal arguments = %lu", arglist->count);
    for (i = 0; i < arglist->count; i++)
        printf("\nArgument %d: \'%s\'", i, arglist->args[i]);

    printf("\n");

    return CMDF_OK;
}

static CMDF_RETURN do_submenu(cmdf_arglist *arglist)
{
    cmdf_init("libcmdf-test/submenu> ", SUBMENU_INTRO, NULL, NULL, 0, 1);

    /* Register our custom commands */
    cmdf_register_command(do_hello, "hello", NULL);
    cmdf_register_command(do_printargs, "printargs", NULL);

    cmdf_commandloop();

    return CMDF_OK;
}

int main(void)
{
    cmdf_init("libcmdf-test> ", PROG_INTRO, NULL, NULL, 0, 1);

    /* Register our custom commands */
    cmdf_register_command(do_hello, "hello", NULL);
    cmdf_register_command(do_submenu, "submenu", NULL);

    cmdf_commandloop();

    return 0;
}
