/*
 *    SAM-QFS_notice_begin
 *
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at pkg/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at pkg/OPENSOLARIS.LICENSE.
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
#ifndef _HOSTS_H
#define	_HOSTS_H

#pragma ident "	$Revision: 1.17 $	"



#include "pub/mgmt/types.h"
#include "pub/mgmt/sqm_list.h"

/*
 * obtain a list of ip addresses and names under which this host is known
 */
int
discover_ip_addresses(
ctx_t *,
sqm_lst_t **addrs); /* list of IP addreses and names */



/*
 * The use of functions below must be coordinated from the client
 * side. Preconditions must be checked on the client side. Calls to
 * each (potential) metadata server host must be made when adding
 * or removing a host and when changing the metadata server.
 */

typedef struct host_info {
	char *host_name;

	/*
	 * ordered elements are char arrays containing dotted decimal,
	 * IPv6 hex or symbolic name
	 */
	sqm_lst_t	*ip_addresses;

	/* Positive numbers are server priority. 0 indicates a client */
	int	server_priority;

	/*
	 * For the metadata server this field indicates how many clients
	 * have the file system mounted including the mds.
	 * Possible values and their meaning:
	 * negative number indicates the mds does not have the fs mounted
	 * or there was an error trying to obtain the number.
	 * 0 indicates no hosts have it mounted.
	 * +number indicates number of servers with the host mounted.
	 */
	int	mounted_hosts;

	/* true if the named host is the current server */
	boolean_t current_server;

} host_info_t;


/*
 * Return an ordered list of the host_info_t structures. The order will
 * match the order in the hosts.<fs_name> file.
 *
 * preconditions:
 * 1. Must be called on a metadata server or potential metadata server.
 */
int
get_host_config(
ctx_t *,
char *fs_name,		/* name of fs to get hosts config for. */
sqm_lst_t **hosts);	/* Ordered list of host_info_t */



/*
 * Remove a host from the hosts.<fs_name> file for a shared file system.
 * If the host being removed is the metadata server, the hosts file will be
 * removed.
 *
 * preconditions:
 * 1. file system must be unmounted on all hosts.
 * 2. This function must be called on a metadata server or a potential metadata
 *    server.
 */
int
remove_host(
ctx_t *ctx,
char *fs_name,		/* name of shared fs from which to remove host */
char *host_name);	/* name of host to remove */



/*
 * This might be needed in 4.3
 * Set what host is the server for the shared file system.
 *
 * preconditions:
 * 1. file system must be unmounted on all hosts
 * 2. Should be called on the current metadata server
 */
int
change_metadata_server(ctx_t *, uname_t new_server);



/*
 * Function to add/modify a host in the hosts.<fs_name> file of a shared file
 * system. If the host already exists it will have its fields updated based
 * on in the input host_info_t.
 *
 * This function does not need to be called when creating the file system on
 * a metadata server nor when creating the file system on a potential metadata
 * server. However when creating a shared file system on a client, this
 * function must be called on the metadata server or a potential metadata
 * server to add the new client.
 *
 * preconditions:
 * 1. The function must be called on the metadata server
 * or on a potential metadata server for the file system.
 */
int
add_host(ctx_t *ctx,
char *fs_name,		/* Name of fs to add host for. */
host_info_t *h);	/* host to add */


/*
 * Setup the advanced network configuration for a shared file system.
 * This method will replace the existing configuration.
 * The host_strs should be in the format specified for
 * getAdvancedNetCfg
 */
int
set_advanced_network_cfg(ctx_t *c, char *fs_name, sqm_lst_t *host_strs);


/*
 * return a list of key value pairs describing the advanced network
 * configuration for a shared file system. This information comes
 * from the hosts.<fsName>.local file. If there is no hosts.<fsName>.local
 * file an empty list will be returned.
 *
 * The returned strings will be key value pairs with the following
 * keys:
 * Hostname = <String>,
 * IPaddresses = <space separated list of ip/hostnames>
 */
int
get_advanced_network_cfg(ctx_t *c, char *fs_name, sqm_lst_t **host_strs);


/*
 * This function returns the name of the mds for the named file system
 * If fs_name is null the name of the metadata server for the first
 * shared file system will be returned.
 */
int get_mds_host(ctx_t *c, char *fs_name, char **mds_host);

void free_host_info(host_info_t *h);
void free_list_of_host_info(sqm_lst_t *l);


#endif	/* _HOSTS_H */
