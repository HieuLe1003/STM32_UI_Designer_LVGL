SET(SOURCES screens/ui_MainMenu.c
    screens/ui_ManualScreen.c
    screens/ui_SettingScreen.c
    screens/ui_InfoScreen.c
    screens/ui_AutoScreen.c
    screens/ui_ViewDataScreen.c
    screens/ui_CalibrationScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_1340268884.c
    images/ui_img_play_circle_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_back_hand_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_center_focus_strong_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_multimodal_hand_eye_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_data_table_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_dashboard_customize_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_location_on_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_settings_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_home_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_security_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_license_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_info_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c
    images/ui_img_1617842459.c
    images/ui_img_undo_50dp_e3e3e3_fill0_wght400_grad0_opsz48_png.c)

add_library(ui ${SOURCES})
