/* NEK Tech shell */
/*
 * nektech-shell.h - Linux Shell 
 *
 * Copyright (C) NEK Tech 2013
 * Developers V1.0:     Deepika Pandey
 *                      Pallavi Gadge
 *                      Shubhangi Maheshwari
 * Author and Architect: Pankaj Saraf
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms and conditions of NEK Tech.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define MAX_LEN 1024
#define MAX_ARG 16

/* NEK Tech Shell:
 * Changes Directory of the shell process.
 */
void change_dir(char *argv[]);

/* NEK Tech Shell:
 * Executes the command in traditional fork/exec manner.
 */
void run_cmd(char *argv[]);

