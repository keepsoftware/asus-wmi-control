#include <linux/module.h>
#include <linux/hid.h>
#include <linux/input.h>

#define KEY_AIRPLANE 0x240

static void ite5570_event(struct input_dev *dev, unsigned int type, unsigned int code, int value);

// create the event handler for the disabled wifi


static int ite5570_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
    struct input_dev *input_dev;

    input_dev = devm_input_allocate_device(&hdev->dev);
    if (!input_dev)
        return -ENOMEM;

    input_dev->name = "ITE5570";
    input_dev->phys = NULL;
    input_dev->id.bustype = BUS_USB;
    input_dev->id.vendor = id->vendor;
    input_dev->id.product = id->product;
    // input_dev->id.version = id->version;
    input_dev->id.version = 0;


    hid_hw_request(hdev, HID_REQ_SET_IDLE, NULL);
    hid_hw_request(hdev, HID_REQ_SET_PROTOCOL, &hdev->boot_protocol);


    set_bit(EV_KEY, input_dev->evbit);
    set_bit(KEY_AIRPLANE, input_dev->keybit);

    input_dev->event = ite5570_event;

    if (input_register_device(input_dev))
        return -ENODEV;

    hid_info(hdev, "ITE5570 device registered\n");

    return 0;
}

static void ite5570_remove(struct hid_device *hdev)
{
    struct input_dev *input_dev = hid_get_drvdata(hdev);

    input_unregister_device(input_dev);
}

static const struct hid_device_id ite5570_devices[] = {
    { HID_USB_DEVICE(0x048D, 0x8051) },
    {},
};
MODULE_DEVICE_TABLE(hid, ite5570_devices);

static struct hid_driver ite5570_driver = {
    .name = "ITE5570",
    .id_table = ite5570_devices,
    .probe = ite5570_probe,
    .remove = ite5570_remove,
};

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Seu Nome");
MODULE_DESCRIPTION("Driver para tecla airplane no notebook Asus");
MODULE_VERSION("0.1");

static void ite5570_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)
{
    if (type == EV_KEY && code == KEY_AIRPLANE) {
        printk(KERN_INFO "Tecla airplane pressionada\n");
        input_report_key(dev, code, value);
        input_sync(dev);
    }
}

module_hid_driver(ite5570_driver);
