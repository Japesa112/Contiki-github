#include "contiki.h"
#include "net/netstack.h"
#include "net/packetbuf.h"

PROCESS(interference_process, "Interference Generator");
AUTOSTART_PROCESSES(&interference_process);

PROCESS_THREAD(interference_process, ev, data) {
  static struct etimer timer;
  PROCESS_BEGIN();

  // Generate interference every 100ms
  etimer_set(&timer, CLOCK_SECOND / 10);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    packetbuf_copyfrom("NOISE", 5); // Dummy packet
    NETSTACK_MAC.send(NULL, NULL); // Broadcast
    etimer_reset(&timer);
  }

  PROCESS_END();
}
