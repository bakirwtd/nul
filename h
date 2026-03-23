local lib = {}

local btnface = Font.new("rbxasset://fonts/families/Inconsolata.json", Enum.FontWeight.Regular, Enum.FontStyle.Normal)
local catface = Font.new("rbxasset://fonts/families/Inconsolata.json", Enum.FontWeight.Bold, Enum.FontStyle.Normal)
local RunService = game:GetService("RunService")
local tween = game:GetService("TweenService")
local UserInputService = game:GetService("UserInputService")

local function lerp(a, b, c)
    return a + (b - a) * c
end

local function getmouse()
    local GuiService = game:GetService("GuiService")
    return UserInputService:GetMouseLocation() - GuiService:GetGuiInset()
end

local function circle(btn, pos)
    local new = Instance.new("Frame")
    local corner = Instance.new("UICorner", new)
    corner.CornerRadius = UDim.new(1, 0)
    new.Name = "circle"
    new.Parent = btn
    new.Size = UDim2.fromOffset(50, 50)
    new.BackgroundColor3 = Color3.fromRGB(btn.BackgroundColor3.R * 255 + 30, btn.BackgroundColor3.G * 255 + 30,
        btn.BackgroundColor3.B * 255 + 30)
    new.BorderSizePixel = 0
    new.ZIndex = 100
    new.AnchorPoint = Vector2.new(0.5, 0.5)

    local pos = getmouse()
    local newpos = UDim2.fromOffset(pos.X - btn.AbsolutePosition.X, pos.Y - btn.AbsolutePosition.Y)
    new.Position = newpos

    task.spawn(function()
        tween:Create(new, TweenInfo.new(.3, Enum.EasingStyle.Quad, Enum.EasingDirection.Out), {
            Size = UDim2.fromOffset(80, 80),
            BackgroundTransparency = 1
        }):Play()
        wait(.3)
        new:Destroy()
    end)
end

lib.new = function()
    local tbl = {}

    local nulllib = Instance.new("ScreenGui")
    nulllib.Name = "null.lib"
    nulllib.Parent = game:GetService("CoreGui")
    nulllib.IgnoreGuiInset = false

    function tbl:exit()
        nulllib:Destroy()
    end

    local container = Instance.new("Frame")
    container.Name = "container"
    container.Parent = nulllib
    container.BackgroundTransparency = 1
    container.BorderSizePixel = 0
    container.Position = UDim2.new(0, 30, 0, 30)
    container.Size = UDim2.new(0.1, 0, 0, 40)

    local layout = Instance.new("UIListLayout")
    layout.Name = "layout"
    layout.Parent = container
    layout.FillDirection = Enum.FillDirection.Horizontal
    layout.Padding = UDim.new(0.1, 0)

    function tbl:Tab(name)
        local tabtbl = {}

        local toggled = false

        local tab = Instance.new("Frame")
        tab.Name = name
        tab.Parent = container
        tab.BackgroundTransparency = 1
        tab.BorderSizePixel = 0
        tab.Size = UDim2.new(1, 0, 1, 0)

        local main = Instance.new("Frame")
        main.Name = "main"
        main.Parent = tab
        main.BackgroundColor3 = Color3.fromRGB(31, 39, 47)
        main.BorderSizePixel = 0
        main.Size = UDim2.new(1, 0, 1, 0)
        main.ZIndex = 2

        local tabName = Instance.new("TextLabel")
        tabName.Name = "tabName"
        tabName.Parent = main
        tabName.BackgroundTransparency = 1
        tabName.BorderSizePixel = 0
        tabName.Size = UDim2.new(1, 0, 1, 0)
        tabName.FontFace = catface
        tabName.Text = name
        tabName.TextColor3 = Color3.fromRGB(255, 255, 255)
        tabName.TextSize = 30
        tabName.ZIndex = 4

        local corner = Instance.new("UICorner")
        corner.CornerRadius = UDim.new(0.4, 0)
        corner.Name = "corner"
        corner.Parent = main

        local body = Instance.new("Frame")
        body.Name = "body"
        body.Parent = tab
        body.BackgroundColor3 = Color3.fromRGB(24, 30, 36)
        body.BorderSizePixel = 0
        body.Position = UDim2.new(0, 0, 0.5, 0)
        body.Size = UDim2.new(1, 0, 0, 0)

        local bottom = Instance.new("Frame")
        bottom.Name = "bottom"
        bottom.Parent = body
        bottom.AnchorPoint = Vector2.new(0, 0.5)
        bottom.BackgroundColor3 = Color3.fromRGB(24, 30, 36)
        bottom.BorderSizePixel = 0
        bottom.Position = UDim2.new(0, 0, 1, 0)
        bottom.Size = UDim2.new(1, 0, 0, 40)
        bottom.ZIndex = 0

        local corner_2 = Instance.new("UICorner")
        corner_2.CornerRadius = UDim.new(0.4, 0)
        corner_2.Name = "corner"
        corner_2.Parent = bottom

        local scroll = Instance.new("ScrollingFrame")
        scroll.Name = "scroll"
        scroll.Parent = body
        scroll.Active = true
        scroll.AnchorPoint = Vector2.new(0, 1)
        scroll.BackgroundTransparency = 1
        scroll.BorderSizePixel = 0
        scroll.Position = UDim2.new(0, 0, 1, 0)
        scroll.Size = UDim2.new(1, 0, 1, -30)
        scroll.CanvasSize = UDim2.new(0, 0, 0, 0)
        scroll.ScrollBarThickness = 0
        scroll.AutomaticCanvasSize = Enum.AutomaticSize.Y

        local trigger = Instance.new("TextButton")

        trigger.Name = "trigger"
        trigger.Parent = main
        trigger.BackgroundColor3 = main.BackgroundColor3
        trigger.BackgroundTransparency = 1
        trigger.BorderSizePixel = 0
        trigger.Size = UDim2.new(1, 0, 1, 0)
        trigger.Text = ""
        trigger.ZIndex = 5
        trigger.ClipsDescendants = true
        trigger.MouseButton1Click:Connect(function()
            toggled = not toggled
            for _, v in pairs(scroll:GetChildren()) do
                if v:IsA("TextButton") then
                    v.Visible = toggled
                end
            end
            circle(trigger)
        end)

        local layout_2 = Instance.new("UIListLayout")
        layout_2.Name = "layout"
        layout_2.Parent = scroll
        layout_2.SortOrder = Enum.SortOrder.LayoutOrder
        layout_2.Padding = UDim.new(0, 10)

        function tabtbl:Btn(name, call)
            local TextButton = Instance.new("TextButton")
            local corner_3 = Instance.new("UICorner")
            local defaultcolor = Color3.fromRGB(31, 39, 47)
            local hovercolor = Color3.fromRGB(53, 66, 80)
            TextButton.Parent = scroll
            TextButton.BackgroundColor3 = defaultcolor
            TextButton.BorderSizePixel = 0
            TextButton.Size = UDim2.new(1, 0, 0, 40)
            TextButton.AutoButtonColor = false
            TextButton.FontFace = btnface
            TextButton.TextColor3 = Color3.fromRGB(255, 255, 255)
            TextButton.TextSize = 30
            TextButton.Text = name
            TextButton.Visible = false
            TextButton.ClipsDescendants = true
            TextButton.TextScaled = true

            local UITextSizeConstraint = Instance.new("UITextSizeConstraint")
            UITextSizeConstraint.Parent = TextButton
            UITextSizeConstraint.MaxTextSize = 30

            local hovering = false

            TextButton.MouseEnter:Connect(function()
                hovering = true
            end)
            TextButton.MouseLeave:Connect(function()
                hovering = false
            end)

            RunService.RenderStepped:Connect(function()
                TextButton.BackgroundColor3 = TextButton.BackgroundColor3:Lerp(hovering and hovercolor or defaultcolor,
                    .1)
            end)

            corner_3.CornerRadius = UDim.new(0.4, 0)
            corner_3.Name = "corner"
            corner_3.Parent = TextButton

            TextButton.MouseButton1Click:Connect(function()
                call()
                circle(TextButton)
            end)
        end

        function tabtbl:Tgl(name, default, call)
            local tgl = {}
            local Toggle = Instance.new("TextButton")
            local corner = Instance.new("UICorner")

            local state = default

            local oncolor = Color3.fromRGB(22, 43, 24)
            local offcolor = Color3.fromRGB(43, 22, 22)
            local ontextcolor = Color3.fromRGB(124, 200, 112)
            local offtextcolor = Color3.fromRGB(200, 88, 118)

            local oncolorhovering = Color3.fromRGB(39, 77, 42)
            local offcolorhovering = Color3.fromRGB(81, 41, 41)

            Toggle.Name = "Toggle"
            Toggle.Parent = scroll
            Toggle.BackgroundColor3 = Color3.fromRGB(22, 43, 24)
            Toggle.BorderColor3 = Color3.fromRGB(0, 0, 0)
            Toggle.BorderSizePixel = 0
            Toggle.Size = UDim2.new(1, 0, 0, 40)
            Toggle.AutoButtonColor = false
            Toggle.FontFace = btnface
            Toggle.TextColor3 = Color3.fromRGB(124, 200, 112)
            Toggle.TextSize = 30
            Toggle.Visible = false
            Toggle.ClipsDescendants = true
            Toggle.Text = name
            Toggle.TextScaled = true

            local UITextSizeConstraint = Instance.new("UITextSizeConstraint")
            UITextSizeConstraint.Parent = Toggle
            UITextSizeConstraint.MaxTextSize = 30

            Toggle.MouseButton1Click:Connect(function()
                state = not state
                call(state)
            end)

            function tgl:bindTo(key, hold)
                warn("Bound")
                UserInputService.InputBegan:Connect(function(input, gameProcessedEvent)
                    if input.KeyCode == key then
                        state = (hold or not state)
                        call(state)
                        warn("Hold key works")
                    end
                end)
                if hold then
                    UserInputService.InputEnded:Connect(function(input, gameProcessedEvent)
                        if input.KeyCode == key then
                            state = false
                            call(state)
                            warn("Hold key works")
                        end
                    end)
                end
            end

            local hovering = false

            Toggle.MouseEnter:Connect(function()
                hovering = true
            end)
            Toggle.MouseLeave:Connect(function()
                hovering = false
            end)

            corner.CornerRadius = UDim.new(0.4, 0)
            corner.Name = "corner"
            corner.Parent = Toggle

            RunService.RenderStepped:Connect(function()
                Toggle.BackgroundColor3 = Toggle.BackgroundColor3:Lerp(state and
                                                                           (hovering and oncolorhovering or oncolor) or
                                                                           (hovering and offcolorhovering or offcolor),
                    .1)
                Toggle.TextColor3 = Toggle.TextColor3:Lerp(state and ontextcolor or offtextcolor, .1)
            end)
            return tgl
        end

        function tabtbl:Text(name, call)
            local TextButton = Instance.new("TextButton")
            local corner_3 = Instance.new("UICorner")
            local defaultcolor = Color3.fromRGB(31, 39, 47)
            local hovercolor = Color3.fromRGB(53, 66, 80)
            TextButton.Parent = scroll
            TextButton.BackgroundColor3 = defaultcolor
            TextButton.BorderSizePixel = 0
            TextButton.Size = UDim2.new(1, 0, 0, 40)
            TextButton.AutoButtonColor = false
            TextButton.FontFace = btnface
            TextButton.TextColor3 = Color3.fromRGB(255, 255, 255)
            TextButton.TextSize = 30
            TextButton.Text = name
            TextButton.Visible = false
            TextButton.ClipsDescendants = true
            TextButton.TextScaled = true

            local UITextSizeConstraint = Instance.new("UITextSizeConstraint")
            UITextSizeConstraint.Parent = TextButton
            UITextSizeConstraint.MaxTextSize = 30

            local hovering = false

            TextButton.MouseEnter:Connect(function()
                hovering = true
            end)
            TextButton.MouseLeave:Connect(function()
                hovering = false
            end)

            RunService.RenderStepped:Connect(function()
                TextButton.BackgroundColor3 = TextButton.BackgroundColor3:Lerp(hovering and hovercolor or defaultcolor,
                    .1)
            end)

            corner_3.CornerRadius = UDim.new(0.4, 0)
            corner_3.Name = "corner"
            corner_3.Parent = TextButton

            TextButton.MouseButton1Click:Connect(function()
                circle(TextButton)
                local input = Instance.new("Frame")
                local gradient = Instance.new("UIGradient")
                local corner = Instance.new("UICorner")
                local box = Instance.new("TextBox")
                local UITextSizeConstraint = Instance.new("UITextSizeConstraint")

                input.Name = "input"
                input.Parent = nulllib
                input.AnchorPoint = Vector2.new(0.5, 0.5)
                input.BackgroundColor3 = Color3.fromRGB(31, 39, 47)
                input.BorderColor3 = Color3.fromRGB(0, 0, 0)
                input.BorderSizePixel = 0
                input.Position = UDim2.new(0.5, 0, 0.5, 0)
                input.Size = UDim2.new(0, 0, 0, 0)
                tween:Create(input, TweenInfo.new(.2, Enum.EasingStyle.Quart, Enum.EasingDirection.Out), {
                    Size = UDim2.new(0.1, 0, 0.1, 0)
                }):Play()

                gradient.Color = ColorSequence.new {ColorSequenceKeypoint.new(0.00, Color3.fromRGB(255, 255, 255)),
                                                    ColorSequenceKeypoint.new(1.00, Color3.fromRGB(216, 216, 216))}
                gradient.Rotation = 45
                gradient.Name = "gradient"
                gradient.Parent = input

                corner.CornerRadius = UDim.new(0.2, 0)
                corner.Name = "corner"
                corner.Parent = input

                box.Name = "box"
                box.Parent = input
                box.BackgroundColor3 = Color3.fromRGB(255, 255, 255)
                box.BackgroundTransparency = 1
                box.BorderColor3 = Color3.fromRGB(0, 0, 0)
                box.BorderSizePixel = 0
                box.Size = UDim2.new(1, 0, 1, 0)
                box.Font = Enum.Font.Unknown
                box.PlaceholderColor3 = Color3.fromRGB(13, 16, 22)
                box.PlaceholderText = "Enter new value.."
                box.Text = ""
                box.TextColor3 = Color3.fromRGB(255, 255, 255)
                box.TextScaled = true
                box.TextSize = 40
                box.TextWrapped = true

                box:CaptureFocus()
                box.FocusLost:Connect(function(entered)
                    if entered then
                        call(tonumber(box.Text))
                    end
                    tween:Create(input, TweenInfo.new(.2, Enum.EasingStyle.Quart, Enum.EasingDirection.In), {
                        Size = UDim2.new(0, 0)
                    }):Play()
                    wait(.3)
                    box:Destroy()
                end)

                UITextSizeConstraint.Parent = box
                UITextSizeConstraint.MaxTextSize = 40
            end)
        end

        function tabtbl:Label(text)
            local Label = Instance.new("TextButton")
            Label.Name = "Label"
            Label.Parent = scroll
            Label.BackgroundTransparency = 1
            Label.BorderSizePixel = 0
            Label.Size = UDim2.new(1, 0, 0, 40)
            Label.AutoButtonColor = false
            Label.FontFace = btnface
            Label.Text = text
            Label.TextColor3 = Color3.fromRGB(255, 255, 255)
            Label.TextSize = 30
            Label.TextScaled = true
            Label.Visible = false

            local UITextSizeConstraint = Instance.new("UITextSizeConstraint")
            UITextSizeConstraint.Parent = Label
            UITextSizeConstraint.MaxTextSize = 30
        end

        return tabtbl
    end
    RunService.RenderStepped:Connect(function()
        for _, v in pairs(container:GetChildren()) do
            if v:IsA("Frame") then
                local scrl = v.body.scroll

                local btns = 0
                local minscale = 1.8
                local ysize = 40
                local padding = 10

                for _, v in pairs(scrl:GetChildren()) do
                    if v:IsA("TextButton") and v.Visible then
                        btns = btns + 1
                    end
                end
                btns = math.min(btns, 10)

                local yoff = (ysize + padding) * (btns - 1)
                if btns == 0 then
                    yoff = 0
                end

                local final = UDim2.new(1, 0, btns > 0 and minscale or 0, yoff)

                scrl.Parent.Size = scrl.Parent.Size:Lerp(final, 0.1)
            end
        end
    end)
    return tbl
end

return lib
