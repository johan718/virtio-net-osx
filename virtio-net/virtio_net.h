/* Copyright 2011 Phil Jordan <phil@philjordan.eu>
 * Dual-licensed under the 3-clause BSD License and the zLib license */

#ifndef VIRTIO_NET_H
#define VIRTIO_NET_H

#include <IOKit/network/IOEthernetController.h>

class IOBufferMemoryDescriptor;
class IOPCIDevice;

struct virtio_net_virtqueue
{
	IOBufferMemoryDescriptor* buf;
};

class eu_philjordan_virtio_net : public IOEthernetController
{
	OSDeclareDefaultStructors(eu_philjordan_virtio_net);

public:
	/// Constructor. Will eventually initialise various internal state.
	virtual bool init(OSDictionary * properties);
	/// Called after device matching. Verifies that the device (the provider) is in fact a device supported by this driver.
	virtual IOService* probe(IOService* provider, SInt32* score);

	/// Initialises the device.
	/** Right now, this is only basic PCI stuff, eventually this should also bring
	 * up an ethernet interface.
	 */
	virtual bool start(IOService* provider);
	virtual void stop(IOService* provider);
	
	/// Destructor, frees internal state
	virtual void free();
	
	virtual IOReturn getHardwareAddress(IOEthernetAddress* addrP);

protected:
	bool setupVirtqueue(uint16_t queue_id, virtio_net_virtqueue& queue);
	
	/// The provider device. NOT retained.
	IOPCIDevice* pci_dev;
	/// Memory mapping of the virtio PCI configuration registers
	IOMemoryMap* pci_config_mmap;
	virtio_net_virtqueue rx_queue;
};

#endif
