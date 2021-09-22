#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <m2tp-member.h>

void onConnected(m2tp_channel);
void onReceive(m2tp_channel, m2tp_byte, m2tp_bytes);
void onDisconnected();

int main()
{
  m2tp_onConnected = &onConnected;
  m2tp_receivedListener = &onReceive;
  m2tp_onDisconnected = &onDisconnected;
  if (!m2tp_connectViaCAN("vcan1", 0, "m"))
  {
    perror("Failed to connect via vcan1");
    return EXIT_FAILURE;
  }

  char buffer[253];
  while (true)
  {
    if (!m2tp_isConnected())
    {
      sleep(1);
      continue;
    }

    memset(buffer, 0, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);

    m2tp_startSend(0);
    for (unsigned int i = 0; i < sizeof(buffer); i++)
    {
      char each = buffer[i];
      m2tp_write(each);
      if (each == '\0')
        break;
    }
    m2tp_writeFinish();

    printf("[SENT]\n");
  }

  return EXIT_SUCCESS;
}

void onConnected(m2tp_channel address)
{
  printf("[INFO] Connected as address #%d\n", address);
}

void onReceive(m2tp_channel fromAddress, m2tp_byte size, m2tp_bytes data)
{
  printf("from #%d: %.*s\n", fromAddress, size, data);
}

void onDisconnected()
{
  printf("[INFO] Disconnected\n");
}
