# Ping Pong
#### Video Demo:  <https://youtu.be/zIRmnI_1Odk>
#### Description:  This is a simple, retro Ping Pong game made using Lua with Love and Atom as the IDE.There is one player, one ball and one AI.The player can control his rectangular bar using the keys "w" and "s", which will move the bar up and down respectively.To score a point, the player must deflect the ball and ensure that the ball gets past the AI rectangular bar, similar to the one the player has.Likewise, the AI scores a point if it deflects the ball and gets it past the player's bar.There is a small ball which will bounce of player, AI, and walls.Once a point is scored, the ball returns to the middle and goes to the direction of whoever scored the point.Initially the ball will go towards the player.Each time the ball collides with the player or AI, it will have a small increase in speed, until a point is scored which it will return to its default speed.ai.lua is to create the AI that will be the player's opponent.I made it such that the AI will track the ball.Initially, when the ball did not increase its speed everytime it hit a player,the AI was unbeatable.However, now the AI is able to be defeated since the ball can move faster than it.ball.lua is for creaating the ball.conf.lua is for generating the gaming interface for the player inculuding the dimensions of the screen they are playing on.main.lua contains all the requiremnts for the game to run by mentioning ai, ball and player.

For my final project for cs50, I have decided to make a video game.
Initially, I was brainstroming ideas for what to haev for my final project.
I thought about making a photo filter to recreate the photo effect from a film camera.
I have also thought about creating a chrome tab extension for checking stock prices quickly and easily.
However, the more i thought about the project, the longer it took me to get started on it.
In the end, I chose to settle on making a video game as I have always loved playing them.
I was interested in creating one as I knew I could tailor the game to my preferences.
I started off with downloading Love and Atom for my IDE.
Then I started researching online the basics of Love language and started experimenting with them.
I wanted to create a game like Mario but I had trouble getting the assests as they mentioned copyright infringement
which honestly scared me as I did not want any trouble.
Thus, I decided to make the simplest game, Ping Pong.
I remember seeing this on some old movies and I thought it would be cool to recreate the logic.
I started off with creating the usr interface.
conf.lua contains the interface. It consisits of the dimensions of the playing screen

function love.conf(t)
    t.title = "Ping Pong"                  -- The title of the window the game is in (string)
    t.version = "11.3"                    -- The LÖVE version this game was made for (string)
    t.console = true                     -- Attach a console (boolean, Windows only)
    t.window.width = 1280                 -- The window width (number)
    t.window.height = 720                 -- The window height (number)
end

Then I had to create main.lua to contain the references to all the other components of my project,
so that they can be called upon. There is load, update and draw which allows the other files of code to be
shown on the screen.
It also contains the score of both player and AI, and it also includes the instruction for how to move the player.

require("player")
require("ball")
require("ai")

function love.load()
  Player:load()
  Ball:load()
  AI:load()

  Score = {player = 0, ai = 0}
  font = love.graphics.newFont(30)
end


function love.update(dt)
    Player:update(dt)
    Ball:update(dt)
    AI:update(dt)
end


function love.draw()
    Player:draw()
    Ball:draw()
    AI:draw()
    drawScore()
end


function drawScore()
    love.graphics.setFont(font)
    love.graphics.print("Player: "..Score.player, 50, 50)
    love.graphics.print("AI: "..Score.ai, 1000, 50)
    love.graphics.print("W = up, S = down")
end


function checkCollision(a, b)
    if a.x + a.width > b.x and a.x < b.x + b.width and a.y + a.height > b.y and a.y < b.y + b.height then
        return true
    else
        return false
    end
end

Then I created player.lua which created the player controller.
It is a rectangular bar which is able to deflect the ping pong ball away from the player,
and prevent it from getting past the player bar.

Player = {}

function Player:load()
    self.x = 50
    self.y = love.graphics.getHeight() / 2
    self.width = 20
    self.height = 100
    self.speed = 500
end


function Player:update(dt)
    self:move(dt)
    self:checkBoundaries()
end


function Player:move(dt)
    if love.keyboard.isDown("w") then
        self.y = self.y - self.speed * dt
    elseif love.keyboard.isDown("s") then
        self.y = self.y + self.speed * dt
    end
end


function Player:checkBoundaries()
    if self.y < 0 then
        self.y = 0
    elseif self.y + self.height > love.graphics.getHeight() then
        self.y = love.graphics.getHeight() - self.height
    end
end


function Player:draw()
    love.graphics.rectangle("fill", self.x, self.y, self.width, self.height)
end

Then I had to create ball.lua.
In the file, logic for the ball to bounce off walls, players and to score points were all included.
I also modified its speed for it to increase its speed everytime it hits a player bar, making the game
slightly more fun and challenging.
When the ball gets past a player, the other player will score a point, reflected on the screen.
The ball will start in the middle and o towards the player bar first.
When a player scores, the ball will go towards their direcion starting from the middle, and returning
to its original speed.

Ball = {}

function Ball:load()
    self.x = love.graphics.getWidth() / 2
    self.y = love.graphics.getHeight() / 2
    self.width = 20
    self.height = 20
    self.speed = 500
    self.xVel = -self.speed
    self.yVel = 0
end

function Ball:update(dt)
    self:move(dt)
    self:collide()
end

function Ball:collide()
    self:collideWall()
    self:collidePlayer()
    self:collideAI()
    self:score()
end

function Ball:collideWall()
    if self.y < 0 then
        self.y = 0
        self.yVel = -self.yVel
    elseif self.y + self.height > love.graphics.getHeight() then
        self.y = love.graphics.getHeight() - self.height
        self.yVel = -self.yVel
    end
end

function Ball:collidePlayer()
    if checkCollision(self, Player) then
        self.xVel = -self.xVel * 1.1
        local middleBall = self.y + self.height / 2
        local middlePlayer = Player.y + Player.height / 2
        local collisionPosition = middleBall - middlePlayer
        self.yVel = collisionPosition * 5
    end
end

function Ball:collideAI()
    if checkCollision(self, AI) then
        self.xVel = -self.xVel * 1.1
        local middleBall = self.y + self.height / 2
        local middleAI = AI.y + AI.height / 2
        local collisionPosition = middleBall - middleAI
        self.yVel = collisionPosition * 5
    end
end

function Ball:score()
    if self.x < 0 then
        Ball:resetPosition(1)
        Score.ai = Score.ai + 1
    end

    if self.x + self.width > love.graphics.getWidth() then
        Ball:resetPosition(-1)
        Score.player = Score.player + 1
    end
end

function Ball:resetPosition(modifier)
    self.x = love.graphics.getWidth() / 2 - self.width / 2
    self.y = love.graphics.getHeight() / 2 - self.height / 2
    self.yVel = 0
    self.xVel = self.speed * modifier
end

function Ball:move(dt)
    self.x = self.x + self.xVel * dt
    self.y = self.y + self.yVel * dt
end

function Ball:draw()
    love.graphics.rectangle("fill", self.x, self.y, self.width, self.height)
end

Then I created ai.lua, which allows the AI to trak the ball and deflect it without fail each time.
Initially without increasing the ball's speed, the AI was impossible to defeat.
But now it is.
I wanted to create a delay in reaction after every few half seconds to allow the AI to be more beatable,
but it just made it look silly.
So, I decided to boost the ball's speed, making everything look smoother.

AI = {}

function AI:load()
    self.width = 20
    self.height = 100
    self.x = love.graphics.getWidth() - self.width - 50
    self.y = love.graphics.getHeight() / 2
    self.yVel = 0
    self.speed = 600

end

function AI:update(dt)
    self:move(dt)
    self:aquireTarget()
end

function AI:move(dt)
    self.y = self.y + self.yVel * dt
end

function AI:aquireTarget()
    if Ball.y + Ball.height < self.y then
        self.yVel = -self.speed
    elseif Ball.y > self.y + self.height then
        self.yVel = self.speed
    else
        self.yVel = 0
    end
end


function AI:draw()
    love.graphics.rectangle("fill", self.x, self.y, self.width, self.height)
end

Lastly I had run.bat which creates a shortcut to make the game load instantly.

@ECHO

start "" "C:\Program Files\LOVE\lovec" .















