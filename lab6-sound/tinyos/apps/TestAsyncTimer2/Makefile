# COMPONENT = AppGetTracesC
# COMPONENT = AppTestCounterC
COMPONENT = TestAlarmC
# COMPONENT = TestSpikesC

CFLAGS += -I$(SZTETOSDIR)/lib/FastSerial
CFLAGS += -I$(SZTETOSDIR)/lib/atm128timer
CFLAGS += -DPLATFORM_BAUDRATE=230400L

CFLAGS += -DTOGGLE_ON_SLEEP
CFLAGS += -DTOGGLE_AT_1023HZ

include $(MAKERULES)
