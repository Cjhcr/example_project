#pragma once
#include "main.h" // 包含 PROS 與 LVGL
#include <string>
#include <vector>

// 用來儲存每個 Auto 的資料：描述文字 與 函式指標
struct AutonRoutine {
  std::string description;
  void (*function)();
};

class AutonSelector {
public:
  std::vector<AutonRoutine> autons; // 所有的 Auto 列表
  int selected_index = 0;           // 紀錄目前被選到的索引

  // UI 元件指標
  lv_obj_t *list;
  lv_obj_t *desc_label;

  // 加入 auton 列表並渲染介面
  void autons_add(std::initializer_list<AutonRoutine> new_autons);

  // 執行選中的 auto
  void run_selected();

  // 建立視覺化介面
  void build_ui();
};

// 讓所有檔案都能使用這個全域變數
extern AutonSelector auton_selector;
