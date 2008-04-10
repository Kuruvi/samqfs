/*
 *    SAM-QFS_notice_begin
 *
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License")
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 *    SAM-QFS_notice_end
 */

// ident	$Id: ArCopyProc.java,v 1.9 2008/04/10 13:36:27 pg125177 Exp $

package com.sun.netstorage.samqfs.mgmt.arc.job;

public class ArCopyProc {

    private long bytesWritten; // kbytes (fsize_t)
    private long spaceNeeded; // kbytes (fsize_t)
    private long pid;
    private int files;
    private String mediaType, vsn; // of volume being written
    private String oprMsg;
    private int filesWritten;

    private ArCopyProc(long bytesWritten, long spaceNeeded, long pid,
		int files, int filesWritten, String mediaType,
		String vsn, String oprMsg) {
            this.bytesWritten = bytesWritten;
            this.spaceNeeded = spaceNeeded;
            this.pid = pid;
            this.files = files;
            this.filesWritten = filesWritten;
            this.mediaType = mediaType;
            this.vsn = vsn;
	    this.oprMsg = oprMsg;
    }
    long getPID() { return pid; }

    public long getBytesWritten() { return bytesWritten; }
    public long getSpaceNeeded() { return spaceNeeded; }
    public int getFiles() { return files; }
    public int getFilesWritten() { return filesWritten; }
    public String getMediaType() { return mediaType; }
    public String getVSN() { return vsn; }
    public String getOprMsg() { return oprMsg; }

}
