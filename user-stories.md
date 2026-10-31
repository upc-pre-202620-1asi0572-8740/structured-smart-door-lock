# Smart Lock User Stories

## User Stories
These stories describe the perspective of an end-user interacting with the smart lock system.

### US001: Managing Keypad Interactions for Door Access
As a user, I want to interact with the keypad to unlock and lock the door so that I can securely access and protect the secured area.

**Acceptance Criteria**:
- **Scenario 1: User unlocks the door with the correct PIN**
  - **Given** the door is locked and the LCD displays "Door Locked",
  - **When** the user enters the PIN "1234" and presses '#',
  - **Then** the servo moves to the unlock position (0 degrees), the LCD displays "Door Unlocked", and the door unlocks.

- **Scenario 2: User deletes a digit and unlocks**
  - **Given** the door is locked and the LCD displays "Door Locked",
  - **When** the user enters "12", presses 'C' to delete the last digit, enters "34", and presses '#',
  - **Then** the servo moves to the unlock position (0 degrees), the LCD displays "Door Unlocked", and the door unlocks.

- **Scenario 3: User locks the door manually**
  - **Given** the door is unlocked and the LCD displays "Door Unlocked",
  - **When** the user presses '*',
  - **Then** the servo moves to the lock position (180 degrees), the LCD displays "Door Locked", and the door locks.

### US002: Receiving Visual Feedback for PIN Entry
As a user, I want to receive visual feedback on the LCD for my PIN entry so that I know my input is registered and whether it is correct.

**Acceptance Criteria**:
- **Scenario 1: User sees asterisks for PIN digits**
  - **Given** the door is locked and the LCD displays "Door Locked",
  - **When** the user presses '1', '2', and '3',
  - **Then** the LCD displays "***" on the second row, updating with each keypress.

- **Scenario 2: User receives feedback for incorrect PIN**
  - **Given** the door is locked and the LCD displays "Door Locked",
  - **When** the user enters the PIN "5678" and presses '#',
  - **Then** the LCD displays "Incorrect PIN!" for 2 seconds, then returns to "Door Locked", and the door remains locked.