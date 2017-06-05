player = {
	toggle = false;
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
	cc:set_walk_dir(forward, back, left, right, dt);
end