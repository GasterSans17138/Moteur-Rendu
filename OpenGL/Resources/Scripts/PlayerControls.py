#TODO : Find a solution for "Canjump" bool (it come from player class)

print(f"ENGINE : Importing {__name__}")

from EnginePy import *

class PlayerControls():
    def __init__(self, gameObject:GameObject, playerInputs:PlayerInputs) -> None:
        self.gameObject     = gameObject
        self.playerInputs    = playerInputs
        self.mJumpHeight    = 7.5
        self.mSpeed         = 5.0

    def Update(self, deltaTime:float, cam:Camera) ->None:
        if self.gameObject.velocity.y < -20.0:
            self.gameObject.velocity.y = -20.0
        self.gameObject.velocity = Vec3(0.0, self.gameObject.velocity.y, 0.0)

        forward:Vec2 = Vec2(cam.Front.x, cam.Front.z).Normalize()

        if (self.playerInputs.moveForward):
            self.gameObject.velocity -= (Vec3(forward.x, 0.0, forward.y) * self.mSpeed)
        if (self.playerInputs.moveBackward):
            self.gameObject.velocity += (Vec3(forward.x, 0.0, forward.y) * self.mSpeed)

        if (self.playerInputs.moveLeft):
            self.gameObject.velocity += (Vec3(cam.Right.x, 0.0, cam.Right.z) * self.mSpeed)
        if (self.playerInputs.moveRight):
            self.gameObject.velocity -= (Vec3(cam.Right.x, 0.0, cam.Right.z) * self.mSpeed)
    
        if (CanJump and self.playerInputs.moveJump):
            self.gameObject.velocity.y = self.mJumpHeight
            CanJump = False
        
        self.gameObject.Transform.Position += self.gameObject.velocity * deltaTime