#include "auton_selector.hpp"
#include "liblvgl/core/lv_obj_pos.h"

// 實例化全域變數
AutonSelector auton_selector;

// [回呼函數] - 當左邊 List 按鈕被點擊時會觸發的行為
static lv_res_t list_btn_action(lv_obj_t *btn) {
  // 取出該按鈕代表的索引 (Index)
  int index = lv_obj_get_free_num(btn);
  auton_selector.selected_index = index;

  // 將右側標籤文字更新為被選中的內容，給使用者確認當前狀態
  lv_label_set_text(auton_selector.desc_label,
                    auton_selector.autons[index].description.c_str());

  return LV_RES_OK;
}

void AutonSelector::build_ui() {
  // 【左側】建立選單列表 (List)
  list = lv_list_create(lv_scr_act(), NULL);
  lv_obj_set_size(list, 200,
                  240); // V5 螢幕為 480x240，我們讓左邊清單佔寬度 200
  lv_obj_align(list, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0); // 靠左對齊

  // 【右側】建立描述標籤 (Label)
  desc_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(desc_label,
                         LV_LABEL_LONG_BREAK); // 若說明文字過長就自動換行
  lv_obj_set_width(desc_label, 260);           // 剩餘空間為幅寬給右邊 (480-200)
  lv_obj_align(desc_label, NULL, LV_ALIGN_IN_TOP_RIGHT, -10,
               20); // 靠右上角並留些間距

  // 初始進入畫面的系統提示字
  lv_label_set_text(desc_label, "Select an Autonomous \nfrom the left list.");

  // 把資料迴圈掃過，動態加入清單
  for (size_t i = 0; i < autons.size(); i++) {
    // 新增按鈕到列表中，第二個參數是 Icon (我們設為無NULL)，接著是文字
    lv_obj_t *btn =
        lv_list_add(list, NULL, autons[i].description.c_str(), list_btn_action);

    // 將索引(index)儲存在這個按鈕的「自訂參數區」(free_num)
    // 中，點擊時才能調出對應程式！
    lv_obj_set_free_num(btn, i);
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
