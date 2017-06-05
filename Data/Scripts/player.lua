player = {
	toggle = false;
	yaw = 0;
	pitch = 0;
}
function player:update(dt)
	local cc = self.this:get_cc(ComponentType.CharacterController)
	local forward, back, left, right = false,false,false,false
	if events.get_key_down(Keys.w) then
		forward = true;
	end
	if events.get_key_down(Keys.s) then
		back = true;
	end
	if events.get_key_down(Keys.a) then
		left = true;
	end
	if events.get_key_down(Keys.d) then
		right = true;
	end
	if events.get_key_down(Keys.space) then
		cc:jump();
	end
	cc:set_walk_dir(forward, back, left, right, dt);
	local x,y = 0,0
	x = events.get_mouse_relative_x()/2000.0;
	y = events.get_mouse_relative_y()/2000.0;
	local lyaw = 0.2*self.yaw + 0.8*x;
	local lpitch = 0.2*self.pitch + 0.8*y;
	self.yaw = lyaw;
	self.pitch = -lpitch;
	cc:rotate(lyaw, -lpitch);
end