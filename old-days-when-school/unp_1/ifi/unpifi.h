#ifndef		_MYNUPIFI_h_
#define		_MYUNPIFI_H_


#include "myunp.h"
#include <netinet/in.h>
#include <linux/sockios.h>
#include <net/if.h>

#define	IFI_NAME	16
#define IFI_HADDR	8

struct	ifi_info{
	char	ifi_name[IFI_NAME];	//interface name
	short	ifi_index; //interface index
	short	ifi_mtu; //interface MTU
	u_char		ifi_haddr[IFI_HADDR]; //hardware address
	u_short		ifi_hlen; //bytes in hardware : 0 6 8
	short	ifi_flags; //IFI_XXX
	short	ifi_myflags; //my own flags for interface
	struct sockaddr *ifi_addr; //primary address
	struct sockaddr *ifi_brdaddr; //broadcasr address
	struct sockaddr *ifi_dstaddr; //destination address
	struct ifi_info *ifi_next; //list next
};

#define IFI_ALIAS	1

struct ifi_info *get_ifi_info(int, int);
struct ifi_info *GEt_ifi_info(int, int);
void   free_ifi_info(struct ifi_info *);

#endif /* _MYUNPIFI_H_ */
