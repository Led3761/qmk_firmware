# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Build Options
# Change yes to no to disable
#
SWAP_HANDS_ENABLE = no

#OLED
OLED_ENABLE = yes
OLED_DRIVER = ssd1306

#ENCODER
ENCODER_ENABLE = yes

#HAPTIC FEEDBACK
HAPTIC_DRIVER = drv2605l
HAPTIC_ENABLE = no

#PER KEY RGB
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = yes      # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_SUPPORTED = yes

#SPACE SAVING
EXTRAKEY_ENABLE = no
MUSIC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
COMBO_ENABLE = no
KEY_OVERRIDE_ENABLE = no

POINTING_DEVICE_DRIVER = paw3204
POINTING_DEVICE_ENABLE = no

EXTRAFLAGS += -Wno-error

# Ignore some warnings during the build, likely to be fixed before RP2040 PR is merged
ALLOW_WARNINGS = yes

# LTO must be disabled for RP2040 builds
LTO_ENABLE = no

SERIAL_DRIVER = vendor
# WS2812_DRIVER = vendor

# CONVERTER - if you use a listed MCU comment the first line and uncomment the appropiate line
#CONVERT_TO = promicro_rp2040
#CONVERT_TO = kb2040
#CONVERT_TO = blok
CONVERT_TO = elite_pi

# AUDIO 
AUDIO_ENABLE = yes
AUDIO_DRIVER = pwm_hardware

