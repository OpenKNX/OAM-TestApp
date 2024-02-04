function DMYPOC_add(device, online, progress, context) {
  currentCount = device.getParameterByName("DMY_Count");
  if (currentCount < 9) {
    newCount = currentCount + 1;
    device.getParameterByName("DMY_Count").value = newCount;

    for (index = newCount; index > context.Position; index--) {
      source = index - 1;
      target = index;

      DMYPOC_copy(device, source, target);
    }

    DMYPOC_reset(device, context.Position);
  }
}

function DMYPOC_del(device, online, progress, context) {
  currentCount = device.getParameterByName("DMY_Count");
  if (currentCount > 1) {

    start = context.Position + 1;
    for (index = start; index <= currentCount; index++) {
      source = index;
      target = index - 1;
      DMYPOC_copy(device, source, target);
    }

    DMYPOC_reset(device, currentCount); // last
    device.getParameterByName("DMY_Count").value = currentCount - 1;
  }
}

function DMYPOC_copy(device, source, target) {
  device.getParameterByName("DMY_Type" + target).value = device.getParameterByName("DMY_Type" + source).value;
  device.getParameterByName("DMY_Value" + target).value = device.getParameterByName("DMY_Value" + source).value;
}

function DMYPOC_reset(device, position) {
  device.getParameterByName("DMY_Type" + position).value = 0;
  device.getParameterByName("DMY_Value" + position).value = 0;
}