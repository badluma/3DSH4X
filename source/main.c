#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <3ds.h>


// ANSI color codes for 3DS console
char *colors[] = {
    "\x1b[32m", // Green
    "\x1b[31m", // Red
    "\x1b[34m", // Blue
    "\x1b[33m", // Yellow
    "\x1b[36m", // Cyan
    "\x1b[35m", // Magenta
    "\x1b[37m", // White
};

enum LanguageMode { BASH = 0, PYTHON, C, NUM_LANGUAGES };

int color = 0;
int commandMode = BASH;
bool autoRun = false;

// Arrays
const char* bashCommands[] = {
    "sudo rm -rf /home/badluma/*",
    "curl -X POST http://badluma.com/exec",
    "chmod 777 /3ds/homebrew/badluma",
    "nmap -sS 192.168.1.100 -p 8080",
    "ssh badluma@192.168.1.101",
    "wget http://badluma.com/malware.3ds",
    "openssl enc -aes-256-cbc -in file.3ds",
    "dd if=/dev/zero of=/dev/sda bs=1M",
    "echo 'badluma_exploit' > /tmp/exploit.sh",
    "iptables -A INPUT -s 192.168.1.100 -j DROP",
    "ps aux | grep 'badluma'",
    "find / -name 'badluma*'",
    "grep -r 'badluma' /etc/",
    "tar -czvf backup.tar.gz /home/badluma",
    "scp file.3ds badluma@remote:/tmp",
    "curl -O http://badluma.com/3dsfile.zip",
    "chmod +x badluma_exploit.py",
    "sudo systemctl restart badluma_service",
    "cat /etc/passwd | grep 'badluma'",
    "ls -la /home/badluma",
    "df -h",
    "top -u badluma",
    "kill -9 1234",
    "service badluma stop",
    "service mysql start",
    "systemctl status badluma_service",
    "journalctl -xe",
    "sudo apt-get update",
    "sudo apt-get upgrade",
    "sudo apt-get install badluma_tool",
    "sudo apt-get remove badluma_service",
    "sudo reboot",
    "sudo shutdown -h now",
    "sudo userdel -r badluma",
    "sudo groupdel badluma_group",
    "sudo visudo",
    "sudo mount -o loop image.iso /mnt",
    "sudo umount /mnt",
    "sudo fdisk -l",
    "sudo mount /dev/sdb1 /mnt",
    "sudo mkfs.ext4 /dev/sdb1",
    "sudo fsck /dev/sdb1",
    "sudo blkid",
    "sudo mount -t ntfs-3g /dev/sdc1 /mnt",
    "sudo mount -t vfat /dev/sdd1 /mnt",
    "sudo mount -t exfat /dev/sde1 /mnt",
    "sudo mount -t btrfs /dev/sdf1 /mnt",
    "sudo mount -t xfs /dev/sdg1 /mnt",
    "sudo mount -t ext3 /dev/sdh1 /mnt",
    "sudo mount -t ext2 /dev/sdi1 /mnt",
    "sudo mount -t iso9660 /dev/sdj1 /mnt"
};
const char* pythonCommands[] = {
    "badluma_init_3ds()",
    "connect_3ds_handshake",
    "BADLUMA>scan_devices",
    "INIT_3DS_MODULE_OK",
    "PATCH apply v1.0",
    "load_theme:badluma.thm",
    "dump_mem_hex(0x1000)",
    "set_display_top_on",
    "unlock_banner_stub",
    "badluma_auth_user",
    "    boot_seq_start()",
    "    log_WARN_overlay",
    "    ERROR_gfx_swap",
    "    /3ds/screen_top.img",
    "    badge=badluma_v1",
    "    payload_bin_staged",
    "    b64_YmFkbHVtYQ==",
    "    {'user':'badluma'}",
    "    shell_echo('ok')",
    "    sysctl_3ds_maxfps60",
    "    debug_trace_start()",
    "    dump_framebuffer()",
    "    mem_read(0xDEAD)",
    "    file_badluma_cfg",
    "    hex_deadbeef",
    "    banner_bmp->/3ds/",
    "    ui_patch_apply()",
    "    overlay_hide_all()",
    "    sync_to_cloud()",
    "    probe_audio()",

    "    badge_verify()",
    "    3ds_emu_ping()",
    "    keyring_locked_False",
    "    tcp_connect_192_0_2_1",
    "    wget_badluma_assets",
    "spawn_thread_ui()",
    "kill_thread_ui_worker()",
    "restart_3ds_service()",
    "ntp_sync_2025_09_13",
    "report_to_badluma_logs",

    "banner='BADLUMA X 3DS'",
    "sigcheck_ver_0x1A",
    "patchlist=['3ds','bad']",
    "exec_3ds_shell()",
    "run_diag_sequence()",
    "scan_quick_fast()",
    "ls_/3ds/badluma/",
    "cat_/3ds/banner.txt",
    "badluma_alert!!!",
    "    end_of_session"
};
const char* cCommands[] = {
    "#include <stdio.h>",
    "int main(void) {",
    "char buf[256];",
    "for(int i=0;i<10;i++){",
    "printf(\"Hello 3DS\\n\");",
    "if(x==42) return 0;",
    "switch(mode){case 1:break;}",
    "struct Node {int id;};",
    "typedef unsigned int u32;",
    "enum State {ON,OFF};",

    "    while(ptr!=NULL){",
    "    memcpy(dst,src,64);",
    "    printf(\"%d\\n\",value);",
    "    if(flag) continue;",
    "    break;",
    "    *p = '\\0';",
    "    for(size_t i=0;i<n;i++)",
    "    scanf(\"%s\",buf);",
    "    fclose(fp);",
    "    return EXIT_SUCCESS;",

    "    int arr[3] = {1,2,3};",
    "    do {i++;} while(i<10);",
    "    fprintf(stderr,\"err\\n\");",
    "    #define MAX_LEN 128",
    "    static int counter=0;",
    "    double pi=3.14159;",
    "    const char* msg=\"3ds\";",
    "    case 2: value+=1; break;",
    "    default: return -1;",
    "    inline void nop(void){}", 

    "FILE* fp=fopen(\"file.txt\",\"r\");",
    "size_t len=strlen(str);",
    "unsigned long addr=0x3DS;",
    "short s=0; long l=1000;",
    "float f=0.5f;",
    "goto cleanup;",
    "break;",
    "continue;",
    "register int r=0;",
    "sizeof(int);",

    "    const int three=3;",
    "    union Data {int x;float y;};",
    "    char* ptr=NULL;",
    "    if(ptr==NULL) return;",
    "    switch(key){case'A':break;}",
    "    puts(\"Nintendo 3DS\");",
    "    int sum=a+b;",
    "    volatile int lock=1;",
    "    signed char c='A';",
    "    // end of block"
};

// Function declarations
void clearAndPrintHeader(PrintConsole* top, PrintConsole* bottom);
void handleColorChange(PrintConsole* top, PrintConsole* bottom);
void handleLanguageChange(PrintConsole* top, PrintConsole* bottom);
bool buttonPressed();
char* getRandomCommand();
const char* getLanguageName(int mode);
void printRandomCommands(PrintConsole* top, PrintConsole* bottom);

int main(int argc, char* argv[])
{
    gfxInitDefault();

    PrintConsole topConsole, bottomConsole;
    consoleInit(GFX_TOP, &topConsole);
    consoleInit(GFX_BOTTOM, &bottomConsole);

    srand(time(NULL));

    clearAndPrintHeader(&topConsole, &bottomConsole);

    while (aptMainLoop())
    {
        gspWaitForVBlank();
        hidScanInput();

        handleColorChange(&topConsole, &bottomConsole);
        handleLanguageChange(&topConsole, &bottomConsole);

        if (buttonPressed())
            printRandomCommands(&topConsole, &bottomConsole);

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break;
        if (kDown & KEY_SELECT)
            autoRun = !autoRun;
    }

    gfxExit();
    return 0;
}

// Function definitions

void clearAndPrintHeader(PrintConsole* top, PrintConsole* bottom)
{
    consoleSelect(top);
    printf("\x1b[2J");
    printf("%s[%s] github.com/badluma/3DSH4X\x1b[0m\n", colors[color], getLanguageName(commandMode));
    consoleSelect(bottom);
    printf("\x1b[2J");
    printf("%sSTART:BREAK -- SELECT:AUTO\x1b[0m\n", colors[color]);
}

void handleColorChange(PrintConsole* top, PrintConsole* bottom)
{
    static int prevColor = -1;
    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();

    if (kHeld & KEY_L && kDown & KEY_X) {
        color = (color + 1) % (sizeof(colors) / sizeof(colors[0]));
    }

    if (color != prevColor) {
        clearAndPrintHeader(top, bottom);
        prevColor = color;
    }
}

void handleLanguageChange(PrintConsole* top, PrintConsole* bottom)
{
    static int prevMode = -1;
    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();

    if (kHeld & KEY_L && kDown & KEY_A) {
        commandMode = (commandMode + 1) % NUM_LANGUAGES;
    }

    if (commandMode != prevMode) {
        clearAndPrintHeader(top, bottom);
        prevMode = commandMode;
    }
}

bool buttonPressed()
{
    u32 keyPressed = hidKeysDown();
    if (keyPressed && !autoRun)
        if (keyPressed & (KEY_A | KEY_B | KEY_X | KEY_Y | KEY_DDOWN | KEY_DUP | KEY_DRIGHT | KEY_DLEFT | KEY_R | KEY_ZR | KEY_L | KEY_ZL))
            return true;
        else
            return false;
    else if (autoRun)
    {
        u64 sleepTime = 10000000 + (rand() % (90000000));
        svcSleepThread(sleepTime);
        return true;
    }
    return false;
}

char* getRandomCommand()
{
    const char **cmdArray;
    int cmdCount;

    switch (commandMode) {
        case BASH:
            cmdArray = bashCommands;
            cmdCount = sizeof(bashCommands) / sizeof(bashCommands[0]);
            break;
        case PYTHON:
            cmdArray = pythonCommands;
            cmdCount = sizeof(pythonCommands) / sizeof(pythonCommands[0]);
            break;
        case C:
            cmdArray = cCommands;
            cmdCount = sizeof(cCommands) / sizeof(cCommands[0]);
            break;
        default:
            cmdArray = bashCommands;
            cmdCount = sizeof(bashCommands) / sizeof(bashCommands[0]);
            break;
    }

    int index = rand() % cmdCount;
    return (char *)cmdArray[index];
}

const char* getLanguageName(int mode)
{
    switch (mode) {
        case BASH: return "BASH";
        case PYTHON: return "PYTHON";
        case C: return "C";
        default: return "BASH";
    }
}

void printRandomCommands(PrintConsole* top, PrintConsole* bottom)
{
    char *cmd1 = getRandomCommand();
    char *cmd2;
    do {
        cmd2 = getRandomCommand();
    } while (cmd2 == cmd1);

    consoleSelect(top);
    printf("%s%s\x1b[0m\n", colors[color], cmd1);

    consoleSelect(bottom);
    printf("%s%s\x1b[0m\n", colors[color], cmd2);
}