#include "unproute.h"
#include <sys/sysctl.h>
#include <netinet/udp.h>
#include <netinet/ip.h>

int main (int argc, char **argv)
{
	int		mib[4], val;
	size_t	len;
	
	mib[0] = CTL_NET;
	mib[1] = AF_INET;
	mib[2] = IPPROTO_UDP;
	mib[3] = UDPCLI_CHECKSUM;

	len = sizeof(val);
	sysctl(mib, 4, &val, &len, NULL, 0);
	printf("udp checksum flags : %d\n", val);
	exit(0);
}

