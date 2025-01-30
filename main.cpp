#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define TEXT_BOX_HEIGHT 170
#define TEXT_BOX_Y (SCREEN_HEIGHT - TEXT_BOX_HEIGHT)
#define NAME_BOX_HEIGHT 40
#define NAME_BOX_Y (TEXT_BOX_Y - NAME_BOX_HEIGHT)

// Typing animation variables
const char* currentText = "";
char displayedText[512] = "";
int textLength = 0;
int currentCharIndex = 0;
bool typing = true;
bool waitingForInput = false;

int currentScene = 0;
bool nameVisible = true;

// Timer for 5-second delay before skipping
float sceneTimer = 0.0f;
float skipDelay = 1.0f; // 5 seconds delay before allowing scene skip

// Structure for dialogue lines
typedef struct {
    const char* name;  // NULL if no name (scene description)
    const char* text;
} DialogueLine;

// Mystery-driven dialogue sequence
DialogueLine scenes[] = {
    {NULL, "Darkness..."},
    {NULL, "Silence..."},
    {NULL, "An endless void..."},
    {NULL, "Then—a beep..."},
    {"CORA", "[SCANNING] System malfunction detected."},
    {"ZENO", "...What?"}, // He recognizes her voice, but the situation is incomprehensible.
    {NULL, "A flicker from his wrist—the only source of light in the void."},
    {"CORA", "[ERROR] Biological systems: Critical malfunction."},
    {"ZENO", "I know... I can tell."}, // He knows something’s wrong, but he doesn't understand *why*.
    {"CORA", "[ALERT] Hydration levels: 0%."},
    {"CORA", "[ALERT] Internal reserves: Depleted."},
    {"ZENO", "Yeah... I know."}, // The mention of hydration or internal reserves doesn’t mean much to him, as it’s just fact now.
    {"CORA", "[SCAN COMPLETE] Sensory input: Abnormal. Recommendation: Locate resources."},
    {"ZENO", "There’s no need to tell me. I know what’s happening."}, // Zeno is used to Cora’s cold efficiency.
    {"CORA", "[ERROR] Biological life: None detected."},
    {"CORA", "[ERROR] You are the last remnant."},
    {"ZENO", "I know. I’m alone."}, // He’s aware of his isolation—this isn’t news to him.
    {NULL, "He stands in the dark, hearing only Cora’s mechanical voice. The void feels... endless."},
    {"CORA", "[WARNING] Unknown presence detected. Proceed with caution."},
    {"ZENO", "What does it matter?"}, // No one left to care about, no one left to fear.
    {NULL, "The presence grows closer—silent, but unmistakably there."},
    {"CORA", "[ALERT] Anomaly detected at coordinates: 247, 68."},
    {"ZENO", "Coordinates? What difference does it make?"}, // He’s resigned. Coordinates, systems, they're just words now.
    {"CORA", "[ERROR] Memory systems: Fragmented. Unable to identify cause."},
    {"ZENO", "Nothing ever makes sense anymore."}, // His existential despair begins to surface.
    {NULL, "A low hum fills the air, almost imperceptible."},
    {"CORA", "[ERROR] Warning: System error. Unable to process data."},
    {"ZENO", "What else is new?"}, // He’s numb to it all, resigned to the errors and glitches.
    {NULL, "The flicker from his wrist is the only thing that anchors him to reality."},
    {"CORA", "[ALERT] Unknown presence moving towards you."},
    {"ZENO", "I see it."}, // The dread sets in, but he’s seen this before—nothing new, just a continuation of the endless unknown.
    {"CORA", "[SYSTEM WARNING] Critical power failure imminent."},
    {"ZENO", "Does it matter?"}, // The impending failure means nothing to him anymore.
    {"CORA", "[ALERT] Lifeform detected... No biological function identified."},
    {NULL, "Zeno looks into the empty space, but there’s nothing visible. Yet he senses the presence—a threat, perhaps?"},
    {"CORA", "[ERROR] Unable to determine cause of anomaly."},
    {"ZENO", "It’s always like this, isn’t it?"}, // His sense of helplessness is growing. The unknown is his only companion.
    {NULL, "In the silent abyss, the dark forces begin to close in."},
    {"CORA", "[ALERT] Unknown force detected."},
    {"ZENO", "I know."}, // There’s a sense of inevitability in his voice now.
    {NULL, "The light flickers, a final warning. The game of survival continues..."},
    {NULL, "Zeno stands, motionless, at the edge of something far greater than himself."},
};


void StartTyping(const char* text) {
    strncpy(displayedText, "", sizeof(displayedText));
    textLength = strlen(text);
    currentCharIndex = 0;
    typing = true;
    waitingForInput = false;
    sceneTimer = 0.0f;  // Reset timer on new scene
}

void DrawTextBox() {
    // Calculate the position of the dialogue box (centered)
    float boxWidth = SCREEN_WIDTH * 0.9f;
    int boxX = (SCREEN_WIDTH - boxWidth) / 2.0f;
    int boxY = TEXT_BOX_Y;

    // Draw the rounded dialogue box with a border
    DrawRectangleV((Vector2){boxX, boxY},Vector2{ boxWidth, (float)TEXT_BOX_HEIGHT-10}, DARKGRAY);
    DrawRectangleLines(boxX, boxY, boxWidth, (float)TEXT_BOX_HEIGHT-10, WHITE); // Border

    if (nameVisible && scenes[currentScene].name != NULL) {
        float nameBoxHeight = (float)NAME_BOX_HEIGHT;
        float nameBoxY = (float)NAME_BOX_Y;
        DrawRectangleV((Vector2){boxX+30 , nameBoxY-10},(Vector2) {MeasureText("ZENO",24)+30, nameBoxHeight}, DARKGRAY);
        DrawRectangleLines(boxX+30 , nameBoxY-10, MeasureText("ZENO",24)+30, nameBoxHeight, WHITE); // Border
        DrawText(scenes[currentScene].name, boxX + 50, nameBoxY , 24, WHITE);
    }
    
    // Draw the text
    DrawText(displayedText, boxX + 50, boxY + 20, 24, WHITE);
}

void DrawButton() {
    // Create a "Next" button at the bottom-right corner of the screen
    float buttonWidth = 120.0f;
    float buttonHeight = 40.0f;
    float buttonX = SCREEN_WIDTH - buttonWidth - 20.0f;
    float buttonY = SCREEN_HEIGHT - buttonHeight - 20.0f;

    if (waitingForInput && sceneTimer >= skipDelay) {
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){buttonX, buttonY, buttonWidth, buttonHeight}) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentScene++;
            if (currentScene >= sizeof(scenes) / sizeof(scenes[0])) {
                currentScene = 0;
            }
            nameVisible = (scenes[currentScene].name != NULL);
            StartTyping(scenes[currentScene].text);
        }
    }

    DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight, ColorAlpha(DARKGRAY, 0.8f));
    DrawRectangleLines(buttonX, buttonY, buttonWidth, buttonHeight, WHITE);
    DrawText("Next", buttonX + (buttonWidth - MeasureText("Next", 20)) / 2, buttonY + (buttonHeight - 20) / 2, 20, WHITE);
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Zeno's Journey");
    SetTargetFPS(60);

    StartTyping(scenes[currentScene].text);

    while (!WindowShouldClose()) {
        // Timer increment
        if (waitingForInput) {
            sceneTimer += GetFrameTime();
        }

        // Typing animation
        if (!waitingForInput) {
            int len = strlen(scenes[currentScene].text);
            if (currentCharIndex < len) {
                displayedText[currentCharIndex] = scenes[currentScene].text[currentCharIndex];
                displayedText[currentCharIndex + 1] = '\0';
                currentCharIndex++;
            } else {
                waitingForInput = true;
            }
        }

        if (waitingForInput && sceneTimer >= skipDelay) {
            // Allow skipping scene after 5 seconds
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_LEFT_SHIFT)) {
                currentScene++;
                if (currentScene >= sizeof(scenes) / sizeof(scenes[0])) {
                    currentScene = 0;
                }
                nameVisible = (scenes[currentScene].name != NULL);
                StartTyping(scenes[currentScene].text);
            }
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextBox();
        DrawButton();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
