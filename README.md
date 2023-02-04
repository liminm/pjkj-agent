AI project game agent
======================

This is the agent of group B for the game "Jump Sturdy" for the 2020 AI tournament at the TU Berlin AOT.

# Software architechture

The entire system consists of 4 Parts:

```
+-----------------------------------------------------------+
| +------------+   +--------------------------------------+ |
| |  FRONTEND  |   |                BACKEND               | |
| |            |   | +--------------+   +---------------+ | |
| | - Views    |   | |  CONTROLLER  |   |  RULESERVER   | | |
| | - Settings |   | |              |<->|               | | |
| | - Manage   |   | | - Manage DB  |   | - Check move  | | |
| |  - Teams   |   | | - REST API   |   | - Check state | | |
| |  - Players |   | | - Combine    |   +---------------+ | |
| |  - Games   |<->| |   Everything |                     | |
| | - Play     |   | | - Time       |   +---------------+ | |
| |            |   | |   Management |   |    STORAGE    | | |
| |            |   | |              |   |               | | |
| |            |   | |              |<->| - Persistent  | | |
| |            |   | |              |   |   Database    | | |
| |            |   | +--------------+   +---------------+ | |
| +------------+   +--------------------------------------+ |
+-----------------------------------------------------------+
```

