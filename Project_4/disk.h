#ifndef _DISK_H_
#define _DISK_H_

#include <stdio.h>
#include <stdlib.h>

/******************************************************************************/
#define DISK_BLOCKS  16384      /* number of blocks on the disk                */
#define BLOCK_SIZE   4096      /* block size on "disk"                        */

/******************************************************************************/
int make_disk(char *name);     /* create an empty, virtual disk file          */
int open_disk(char *name);     /* open a virtual disk (file) - put fs on top virtual disk */
int close_disk();              /* close a previously opened disk (file) - take fs off virtual disk      */

int block_write(int block, char *buf);
                               /* write a block of size BLOCK_SIZE to disk    */
int block_read(int block, char *buf);
                               /* read a block of size BLOCK_SIZE from disk   */
/******************************************************************************/

#endif

