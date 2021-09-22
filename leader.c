#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <m2tp-leader.h>

void onNewMember(char *, m2tp_channel);
void onReceive(m2tp_channel, m2tp_byte, m2tp_bytes);
void onMemberQuit(m2tp_channel);

volatile m2tp_channel target = 0;

int main()
{
  m2tp_onNewMemberListener = &onNewMember;
  m2tp_receivedListener = &onReceive;
  m2tp_onAnotherMemberQuitListener = &onMemberQuit;
  m2tp_connectViaCAN("vcan0", 0, "l");

  // Found bug here:
  /* if (!m2tp_connectViaCAN("vcan0", 0, "l"))
  {
    perror("Failed to connect via vcan0");
    return EXIT_FAILURE;
  } */

  char buffer[253];
  while (true)
  {
    if (target == 0)
    {
      sleep(1);
      continue;
    }

    memset(buffer, 0, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);

    m2tp_startSend(target);
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

void onNewMember(char *deviceClass, m2tp_channel address)
{
  target = address;
  printf("[INFO] %s connected as address #%d\n", deviceClass, address);
}

void onReceive(m2tp_channel fromAddress, m2tp_byte size, m2tp_bytes data)
{
  printf("from #%d: %.*s\n", fromAddress, size, data);
}

void onMemberQuit(m2tp_channel address)
{
  target = 0;
  printf("[INFO] Device #%d disconnected\n", address);
}
