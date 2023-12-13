local M = {}

M.dap = {
  plugin = true,
  n = {
    ["<leader>db"] = {
      "<cmd> DapToggleBreakpoint <CR>",
      "Add breakpoint at line",
    },
    ["<leader>dr"] = {
      "<cmd> DapContinue <CR>",
      "Start or continue the debugger",
    },
    ["<leader>r"] = {
      "<cmd>!clang++ --debug -std=c++11 % && ./a.out<cr>",
      "Run g++",
    }
  }
}

return M
