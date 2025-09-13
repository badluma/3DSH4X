#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <3ds.h>

// Colors
#define COLOR_RED     0xFF0000FF
#define COLOR_GREEN   0xFF00FF00
#define COLOR_BLUE    0xFFFF0000
#define COLOR_YELLOW  0xFF00FFFF
#define COLOR_CYAN    0xFFFFFF00
#define COLOR_MAGENTA 0xFFFF00FF
#define COLOR_WHITE   0xFFFFFFFF
#define COLOR_BLACK   0xFF000000
#define COLOR_ORANGE  0xFF008FFF
#define COLOR_PURPLE  0xFF800080
#define COLOR_GRAY    0xFF808080

// Variables
u32 kDown;
u32 kHeld;
bool autoRun = false;

// Arrays
const char* commands[] = {
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

// Functions
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
        svcSleepThread(10000000); 
        return true;
    }
    return false;
}

char *getRandomCommand()
{
    int index = rand() % (sizeof(commands) / sizeof(commands[0]));
    return commands[index];
}

int main(int argc, char* argv[])
{
    gfxInitDefault();

    PrintConsole topConsole, bottomConsole;
    consoleInit(GFX_TOP, &topConsole);
    consoleInit(GFX_BOTTOM, &bottomConsole);

    srand(time(NULL));

    // Print initial message on both screens
    consoleSelect(&topConsole);
    printf("\x1b[32mgithub.com/badluma/3DSH4X\x1b[0m\n");
    consoleSelect(&bottomConsole);
    printf("\x1b[32mSTART:BREAK -- SELECT:AUTO\x1b[0m\n");

    while (aptMainLoop())
    {
        gspWaitForVBlank();
        hidScanInput();

        if (buttonPressed())
        {
            // Get two different random commands
            char *cmd1 = getRandomCommand();
            char *cmd2;
            do {
                cmd2 = getRandomCommand();
            } while (cmd2 == cmd1);

            // Print on top screen
            consoleSelect(&topConsole);
            printf("\x1b[32m%s\x1b[0m\n", cmd1);

            // Print on bottom screen
            consoleSelect(&bottomConsole);
            printf("\x1b[32m%s\x1b[0m\n", cmd2);
        }

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break;
        if (kDown & KEY_SELECT)
            autoRun = !autoRun;
    }

    gfxExit();
    return 0;
}
