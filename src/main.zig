const std = @import("std");
const rl = @import("raylib.zig");

const SCREEN_WIDTH = 1200;
const SCREEN_HEIGHT = 800;

pub fn main() !void {
    rl.InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "foo");
    defer rl.CloseWindow();

    rl.SetTargetFPS(60);

    while (!rl.WindowShouldClose()) {
        if (rl.IsKeyPressed(rl.KEY_Q)) break;

        {
            rl.BeginDrawing();
            defer rl.EndDrawing();

            rl.ClearBackground(rl.BLACK);
            rl.DrawText("This is a first window using zig", 190, 200, 20, rl.WHITE);
        }
    }
}
