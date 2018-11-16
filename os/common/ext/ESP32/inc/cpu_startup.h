#define IRAM_ATTR __attribute__((section(".iram1")))


void IRAM_ATTR call_start_cpu0()
{

  //  cpu_configure_region_protection();



    //Clear BSS. Please do not attempt to do any complex stuff (like early logging) before this.
  //  memset(&_bss_start, 0, (&_bss_end - &_bss_start) * sizeof(_bss_start));

    /* Unless waking from deep sleep (implying RTC memory is intact), clear RTC bss */
 //   if (rst_reas[0] != DEEPSLEEP_RESET) {
  //      memset(&_rtc_bss_start, 0, (&_rtc_bss_end - &_rtc_bss_start) * sizeof(_rtc_bss_start));
  //  }

#if CONFIG_SPIRAM_BOOT_INIT
    esp_spiram_init_cache();
    if (esp_spiram_init() != ESP_OK) {
#if CONFIG_SPIRAM_ALLOW_BSS_SEG_EXTERNAL_MEMORY
        ESP_EARLY_LOGE(TAG, "Failed to init external RAM, needed for external .bss segment");
        abort();
#endif

#if CONFIG_SPIRAM_IGNORE_NOTFOUND
        ESP_EARLY_LOGI(TAG, "Failed to init external RAM; continuing without it.");
        s_spiram_okay = false;
#else
        ESP_EARLY_LOGE(TAG, "Failed to init external RAM!");
        abort();
#endif
    }
#endif

  //  ESP_EARLY_LOGI(TAG, "Pro cpu up.");

#if !CONFIG_FREERTOS_UNICORE
  //  if (REG_GET_BIT(EFUSE_BLK0_RDATA3_REG, EFUSE_RD_CHIP_VER_DIS_APP_CPU)) {
  //      ESP_EARLY_LOGE(TAG, "Running on single core chip, but application is built with dual core support.");
  //      ESP_EARLY_LOGE(TAG, "Please enable CONFIG_FREERTOS_UNICORE option in menuconfig.");
  //      abort();
  //  }
 //   ESP_EARLY_LOGI(TAG, "Starting app cpu, entry point is %p", call_start_cpu1);
    //Flush and enable icache for APP CPU
 //   Cache_Flush(1);
 //   Cache_Read_Enable(1);
 //   esp_cpu_unstall(1);
    // Enable clock and reset APP CPU. Note that OpenOCD may have already
    // enabled clock and taken APP CPU out of reset. In this case don't reset
    // APP CPU again, as that will clear the breakpoints which may have already
    // been set.
  //  if (!DPORT_GET_PERI_REG_MASK(DPORT_APPCPU_CTRL_B_REG, DPORT_APPCPU_CLKGATE_EN)) {
   //     DPORT_SET_PERI_REG_MASK(DPORT_APPCPU_CTRL_B_REG, DPORT_APPCPU_CLKGATE_EN);
   //     DPORT_CLEAR_PERI_REG_MASK(DPORT_APPCPU_CTRL_C_REG, DPORT_APPCPU_RUNSTALL);
    //    DPORT_SET_PERI_REG_MASK(DPORT_APPCPU_CTRL_A_REG, DPORT_APPCPU_RESETTING);
    //    DPORT_CLEAR_PERI_REG_MASK(DPORT_APPCPU_CTRL_A_REG, DPORT_APPCPU_RESETTING);
    //}
 //   ets_set_appcpu_boot_addr((uint32_t)call_start_cpu1);

  //  while (!app_cpu_started) {
   //     ets_delay_us(100);
   // }
#else
    ESP_EARLY_LOGI(TAG, "Single core mode");
    DPORT_CLEAR_PERI_REG_MASK(DPORT_APPCPU_CTRL_B_REG, DPORT_APPCPU_CLKGATE_EN);
#endif


#if CONFIG_SPIRAM_MEMTEST
    if (s_spiram_okay) {
        bool ext_ram_ok=esp_spiram_test();
        if (!ext_ram_ok) {
            ESP_EARLY_LOGE(TAG, "External RAM failed memory test!");
            abort();
        }
    }
#endif
#if CONFIG_SPIRAM_ALLOW_BSS_SEG_EXTERNAL_MEMORY
    memset(&_ext_ram_bss_start, 0, (&_ext_ram_bss_end - &_ext_ram_bss_start) * sizeof(_ext_ram_bss_start));
#endif
    /* Initialize heap allocator. WARNING: This *needs* to happen *after* the app cpu has booted.
       If the heap allocator is initialized first, it will put free memory linked list items into
       memory also used by the ROM. Starting the app cpu will let its ROM initialize that memory,
       corrupting those linked lists. Initializing the allocator *after* the app cpu has booted
       works around this problem.
       With SPI RAM enabled, there's a second reason: half of the SPI RAM will be managed by the
       app CPU, and when that is not up yet, the memory will be inaccessible and heap_caps_init may
       fail initializing it properly. */
 //   heap_caps_init();

   // ESP_EARLY_LOGI(TAG, "Pro cpu start user code");
  //  start_cpu0();
}

#if !CONFIG_FREERTOS_UNICORE

static void wdt_reset_cpu1_info_enable(void)
{
 //   DPORT_REG_SET_BIT(DPORT_APP_CPU_RECORD_CTRL_REG, DPORT_APP_CPU_PDEBUG_ENABLE | DPORT_APP_CPU_RECORD_ENABLE);
 //   DPORT_REG_CLR_BIT(DPORT_APP_CPU_RECORD_CTRL_REG, DPORT_APP_CPU_RECORD_ENABLE);
}

void IRAM_ATTR call_start_cpu1()
{
  //  asm volatile (\
  //                "wsr    %0, vecbase\n" \
  //                ::"r"(&_init_start));

    ets_set_appcpu_boot_addr(0);
 //   cpu_configure_region_protection();

#if CONFIG_CONSOLE_UART_NONE
    ets_install_putc1(NULL);
    ets_install_putc2(NULL);
#else // CONFIG_CONSOLE_UART_NONE
    uartAttach();
    ets_install_uart_printf();
  //  uart_tx_switch(CONFIG_CONSOLE_UART_NUM);
#endif

    wdt_reset_cpu1_info_enable();
 //   ESP_EARLY_LOGI(TAG, "App cpu up.");
  //  app_cpu_started = 1;
 //   start_cpu1();
}
#endif //!CONFIG_FREERTOS_UNICORE
