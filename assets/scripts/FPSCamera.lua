
movementSpeed = 1;
mouseSense = 0.001;
cameraComponent = nil;
camera = nil;
lastX = 0;
lastY = 0;
function OnCreate()
  cameraComponent = GetCameraComponent(this);
  camera = cameraComponent.mData;
end

function OnUpdate()
  w = Input.GetKeyState(87);
  a = Input.GetKeyState(65);
  s = Input.GetKeyState(83);
  d = Input.GetKeyState(68);
  ms = Input.GetMouseState();

  if w == 1 or w == 2 then
    m = Vec3.new()
    m.z = movementSpeed;
    camera:moveRelative(m);
  end

  if s == 1 or s == 2 then
    m = Vec3.new()
    m.z = -movementSpeed;
    camera:moveRelative(m);
  end

  if a == 1 or a == 2 then
    m = Vec3.new()
    m.x = -movementSpeed;
    camera:moveRelative(m);
  end

  if d == 1 or d == 2 then
    m = Vec3.new()
    m.x = movementSpeed;
    camera:moveRelative(m);
  end

  if ms.MouseButton1 == 1 then
    deltaX = lastX - ms.x;
    deltaY = lastY - ms.y;
    camera:rotate(deltaY * mouseSense, deltaX * mouseSense, 0);
  end
      lastX = ms.x;
      lastY = ms.y;
end