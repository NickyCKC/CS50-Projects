# Generated by Django 4.0.3 on 2022-09-03 13:16

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0011_rename_imageurl_listing_image_url'),
    ]

    operations = [
        migrations.AlterField(
            model_name='bid',
            name='bid',
            field=models.DecimalField(decimal_places=2, default=0, max_digits=12),
        ),
    ]
