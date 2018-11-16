





MEMORY
{





  iram0_0_seg (RX) : org = 0x40080000, len = 0x20000



  iram0_2_seg (RX) : org = 0x400D0018, len = 0x330000-0x18
  dram0_0_seg (RW) : org = 0x3FFB0000 + 0xdb5c,
                                     len = 0x2c200 - 0xdb5c


  drom0_0_seg (R) : org = 0x3F400018, len = 0x400000-0x18





  rtc_iram_seg(RWX) : org = 0x400C0000, len = 0x2000


  rtc_data_seg(RW) : org = 0x3ff80000, len = 0x2000





  rtc_slow_seg(RW) : org = 0x50000000 + 512,
                                     len = 0x1000 - 512


  extern_ram_seg(RWX) : org = 0x3F800000,
                                     len = 0x400000
}


_heap_end = 0x40000000 - 0x0;

_data_seg_org = ORIGIN(rtc_data_seg);





REGION_ALIAS("rtc_data_location", rtc_slow_seg );
