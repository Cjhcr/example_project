#include "auton_selector.hpp"
#include "liblvgl/lvgl.h"
#include <cstdint>
// 實例化全域變數
AutonSelector auton_selector;

// [回呼函數] - 當左邊 List 按鈕被點擊時會觸發的行為
static void list_btn_action(lv_event_t *e) {
  lv_obj_t *btn = static_cast<lv_obj_t *>(lv_event_get_target(e));
  int index = static_cast<int>(reinterpret_cast<intptr_t>(lv_event_get_user_data(e)));
  auton_selector.selected_index = index;

  // 將右側標籤文字更新為被選中的內容，給使用者確認當前狀態
  lv_label_set_text(auton_selector.desc_label,
                    auton_selector.autons[index].description.c_str());
}

void AutonSelector::build_ui() {
  // 【左側】建立選單列表 (List)
  list = lv_list_create(lv_screen_active());
  lv_obj_set_size(list, 200,
                  240); // V5 螢幕為 480x240，我們讓左邊清單佔寬度 200
  lv_obj_align(list, LV_ALIGN_TOP_LEFT, 0, 0); // 靠左對齊
  lv_obj_set_style_bg_opa(list, LV_OPA_TRANSP, LV_PART_MAIN);
  lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);

  // 【右側】建立描述標籤 (Label)
  desc_label = lv_label_create(lv_screen_active());
  lv_label_set_long_mode(desc_label,
                         LV_LABEL_LONG_WRAP); // 若說明文字過長就自動換行
  lv_obj_set_width(desc_label, 260);           // 剩餘空間為幅寬給右邊 (480-200)
  lv_obj_align(desc_label, LV_ALIGN_TOP_RIGHT, -10,
               20); // 靠右上角並留些間距
  lv_obj_set_style_bg_opa(desc_label, LV_OPA_TRANSP, LV_PART_MAIN);
  lv_obj_set_style_text_color(desc_label, lv_color_white(), LV_PART_MAIN);

  // 初始進入畫面的系統提示字
  lv_label_set_text(desc_label, "Select an Autonomous \nfrom the left list.");

  // 把資料迴圈掃過，動態加入清單
  for (size_t i = 0; i < autons.size(); i++) {
    // 新增按鈕到列表中，第二個參數是 Icon (我們設為無NULL)，接著是文字
    lv_obj_t *btn = lv_list_add_button(list, NULL,
                                      autons[i].description.c_str());
    lv_obj_set_style_bg_opa(btn, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(btn, lv_color_white(), LV_PART_MAIN);

    // 將索引(index)儲存在事件回呼的 user_data 中，點擊時取回對應程式
    lv_obj_add_event_cb(btn, list_btn_action, LV_EVENT_CLICKED,
                        reinterpret_cast<void *>(static_cast<intptr_t>(i)));
  }
}

void AutonSelector::autons_add(std::initializer_list<AutonRoutine> new_autons) {
  autons = new_autons;
  build_ui();
}

void AutonSelector::run_selected() {
  // 確保有資料，且清單選取無誤
  if (!autons.empty() && selected_index >= 0 &&
      selected_index < autons.size()) {
    autons[selected_index].function(); // 執行與該選項對應的 function
  }
}
